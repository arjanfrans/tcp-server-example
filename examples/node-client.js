'use strict';

const net = require('net');
const client = new net.Socket();

const PORT = 8080;
const HOST = '127.0.0.1';

let sendInterval = null;

const CONCURRENCY = 50;
const WRITE_COMMANDS = 20;

let count = 0;
client.connect(PORT, HOST, () => {
    console.log('CONNECTED');

    const writes = [];

    for (let i = 0; i < CONCURRENCY; i++) {
        writes.push(new Promise((resolve) => {
            for (let j = 0; j < WRITE_COMMANDS; j++) {
                const data = `SET "${j}test" "${Math.random()}"\n`;

                setTimeout(() => {
                    client.write(data);
                }, 1000);

                // console.log('writing ' + count);

                count += 1;
            }

            resolve();
        }));
    }

    const reads = [];

    // for (let i = 0; i < CONCURRENCY; i++) {
    //     reads.push(new Promise((resolve) => {
    //         for (let j = 0; j < WRITE_COMMANDS; j++) {
    //             const data = `GET "${0}test" \n`;
    //
    //             client.write(data);
    //
    //             // console.log('reading ' + count);
    //
    //             count += 1;
    //         }
    //
    //         resolve();
    //     }));
    // }

    Promise.all(writes).then(() => {
        return Promise.all(writes);
    }).catch((err) => console.log(err));
});

let received = 0;

client.on('close', () => {
    console.log('CLOSED');
});

function newLineStream (done) {
	let buffer = '';

    return (chunk) => {
        let i = 0
        let piece = '';
        let offset = 0;

		buffer += chunk;

		while ((i = buffer.indexOf('\n', offset)) !== -1) {
			piece = buffer.substr(offset, i - offset);
			offset = i + 1;

			done(piece);
		}

		buffer = buffer.substr(offset);
	};
}

console.time('start');
var myListener = newLineStream( function (message) {
    received += 1;

    if (received === count) {
        console.timeEnd('start');
        console.log('DONE');
    }
});

client.on('data', myListener);
client.on('error', (err) => {
    console.log(err.stack);
});
