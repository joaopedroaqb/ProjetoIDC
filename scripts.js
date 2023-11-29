const { SerialPort } = require('serialport');
const arduino = new SerialPort({ path: 'COM1' });

function controlarLED(estado) {
    arduino.write(estado); 
}

//Ou tentar rodar com esse
/*$(document).ready(function() {
    $("#ligarBtn").click(function() {
        controlarLED('ON');
    });

    $("#desligarBtn").click(function() {
        controlarLED('OFF');
    });

    function controlarLED(estado) {
        $.get('/?LED=' + estado, function(data) {
            // Atualiza o status com base na resposta do servidor
            $("#status").text("Status: " + data);
        });
    }
});
