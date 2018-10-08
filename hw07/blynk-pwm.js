#!/usr/bin/env node
// From Blinks various LEDs
const Blynk = require('blynk-library');
const b = require('bonescript');
const util = require('util');

const LED0 = 'P9_14';
const LED1 = 'P9_13';
const BUTTON = 'P9_15';
b.pinMode(LED0, b.OUTPUT);
b.pinMode(LED1, b.OUTPUT);
b.pinMode(BUTTON, b.INPUT);

const AUTH = 'c449c266fead4afcb37377b6195ab012';

var blynk = new Blynk.Blynk(AUTH);

var v0 = new blynk.VirtualPin(0);
var slider = new blynk.VirtualPin(1);
var v10 = new blynk.WidgetLED(10);
// console.log(util.inspect(v1));
var v9 = new blynk.VirtualPin(9);

v0.on('write', function(param) {
    console.log('V0:', param[0]);
    b.digitalWrite(LED1, param[0]);
});

//v9.on('read', function() {
//  v9.write(b.digitalRead(BUTTON));
//});

b.pinMode(LED0, b.OUTPUT);
slider.on('write', function(param) {
    console.log('Slider:', param[0]);
//    b.pinMode(LED0, b.OUTPUT);
    b.analogWrite(LED0, param[0]);
});

v10.setValue(0);    // Initiallly off

// v9.on('read', function() {
//     v9.write(new Date().getSeconds());
// });

b.attachInterrupt(BUTTON, toggle, b.CHANGE);

function toggle(x) {
    console.log("V1: ", x.value);
    x.value ? v10.turnOff() : v10.turnOn();
}
