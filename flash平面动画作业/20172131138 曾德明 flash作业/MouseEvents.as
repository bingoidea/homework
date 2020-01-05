package {
import flash.display.Sprite;
import flash.events.MouseEvent;
public class MouseEvents extends Sprite {
public function MouseEvents() {
init();
}
private function init():void {
var ball:Sprite = new Sprite();
addChild(ball);
ball.graphics.beginFill(0xff0000);
ball.graphics.drawCircle(0, 0, 50);

ball.graphics.endFill();
ball.x = stage.stageWidth / 2;
ball.y = stage.stageHeight / 2;

//var ball2:Black=new Black();
//addChild(ball2);

ball.addEventListener(MouseEvent.CLICK, onMouseEvent);
ball.addEventListener(MouseEvent.DOUBLE_CLICK,onMouseEvent);
ball.addEventListener(MouseEvent.MOUSE_DOWN,onMouseEvent);
//ball.addEventListener(MouseEvent.MOUSE_MOVE,onMouseEvent);
ball.addEventListener(MouseEvent.MOUSE_OUT,onMouseEvent);
ball.addEventListener(MouseEvent.MOUSE_OVER,onMouseEvent);
ball.addEventListener(MouseEvent.MOUSE_UP,onMouseEvent);
ball.addEventListener(MouseEvent.MOUSE_WHEEL,onMouseEvent);
ball.addEventListener(MouseEvent.ROLL_OUT,onMouseEvent);
ball.addEventListener(MouseEvent.ROLL_OVER,onMouseEvent);
}
public function onMouseEvent(event:MouseEvent):void {
trace(event.type);
}
}
}