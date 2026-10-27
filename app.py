from flask import Flask, jsonify, render_template, request
import os, threading, time
app=Flask(__name__)
state={'RISK':'LOW','SCORE':'0','POTHOLE':'NO','CLOSURE':'NO','PEAK':'NO','AMBULANCE':'OFF','CONNECTED':'DEMO'}
lock=threading.Lock()

def serial_worker():
    try:
        import serial
    except ImportError:
        return
    port=os.environ.get('ARDUINO_PORT','COM3')
    while True:
        try:
            with serial.Serial(port,9600,timeout=1) as ser:
                time.sleep(2)
                while True:
                    line=ser.readline().decode('utf-8',errors='ignore').strip()
                    fields=dict(piece.split('=',1) for piece in line.split(',') if '=' in piece)
                    if 'RISK' in fields:
                        with lock: state.update(fields);state['CONNECTED']='ARDUINO'
        except (serial.SerialException,OSError):
            with lock:state['CONNECTED']='DEMO'
            time.sleep(3)

@app.route('/')
def home():return render_template('index.html')
@app.route('/api/status')
def status():
    with lock:return jsonify(state.copy())
@app.route('/api/demo',methods=['POST'])
def demo():
    with lock:
        if state['CONNECTED']=='ARDUINO':return jsonify({'error':'Arduino connected; use physical buttons'}),409
        data=request.get_json(silent=True) or {}
        for key in ['POTHOLE','CLOSURE','PEAK']:
            if key in data:state[key]='YES' if data[key] else 'NO'
        if 'AMBULANCE' in data:state['AMBULANCE']='ACTIVE' if data['AMBULANCE'] else 'OFF'
        score=2*(state['POTHOLE']=='YES')+3*(state['CLOSURE']=='YES')+2*(state['PEAK']=='YES')
        state['SCORE']=str(score);state['RISK']='HIGH' if score>=2 else 'LOW'
        return jsonify(state.copy())
if __name__=='__main__':
    threading.Thread(target=serial_worker,daemon=True).start()
    app.run(host='127.0.0.1',port=5000,debug=False)
