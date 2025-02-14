const aesCbcMac = require('aes-cbc-mac');
let arg= process.argv.splice(2);
// console.log(arg);
let filename =arg[0].toString();

let ivvalue =arg[1].toString();
// console.log(ivvalue);


const fs = require('fs')
fs.readFile(filename, 'hex' , (err, data) => {
    if (err) {
        console.error(err)
        return
    }
    // console.log(data)
    const message = Buffer.from(data, 'hex');
    const key = Buffer.from(ivvalue, 'hex');
    const hashLen = 8; // bytes, 64 bits
    const hash = aesCbcMac.create(message, key, hashLen);
    console.log(hash.toString('hex'));
})




