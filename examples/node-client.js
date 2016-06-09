'use strict';

const net = require('net');
const client = new net.Socket();

const PORT = 8080;
const HOST = '127.0.0.1';

let sendInterval = null;

client.connect(PORT, HOST, () => {
    console.log('CONNECTED');

    sendInterval = setInterval(() => {
        const data = 'hello';

        console.log(`SENT: ${data}`);

        client.write(data);
    }, 1000);
});

client.on('data', (data) => {
    console.log(`RECEIVED: ${data}`);
});

client.on('close', () => {
    console.log('CLOSED');

    if (sendInterval) {
        clearInterval(sendInterval);
    }
});
