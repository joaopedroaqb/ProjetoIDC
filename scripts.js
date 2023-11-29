const {SeriaPort} = requerie('serialport');
const arduino = new SerialPort({path:'COM1'})

function controlarLED(estado) {
    $.get('/?LED=' + estado);
}
