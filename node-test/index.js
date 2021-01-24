"use strict";
const five = require("johnny-five")
const Koa = require("koa")
const router = require('koa-router')
const routes = router()

const app = new Koa()
const board = new five.Board()
const port = 8000
let led = null

board.on("ready", function() {
  console.log("### Board ready!");
  led = new five.Led(2);
});

routes.get('/test/:param1', async ctx => {
  ctx.body = `hello world ${ctx.params.param1}`
})

routes.get('/led/:mode', async ctx => {
  if(led) {
    var status = "OK";
    switch(ctx.params.mode) {
      case "on":
        led.on();
        break;
      case "off":
        led.off();
        break;
      case "blink":
        led.blink();
        break;
      case "stop":
        led.stop();
        break;
      default:
        status = "Unknown: " + ctx.params.mode;
        break;
    }
    console.log(status)
    ctx.body = status
  } else {
    ctx.body = 'Board NOT ready!'
  }
});

app.use(routes.routes())

app.listen(port, function () {
  console.log('Listening on port ' + port);
});
