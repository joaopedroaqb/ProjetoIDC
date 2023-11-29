const { SerialPort } = require('serialport');
const arduino = new SerialPort({ path: 'COM1' });

function controlarLED(estado) {
    arduino.write(estado); 
}
