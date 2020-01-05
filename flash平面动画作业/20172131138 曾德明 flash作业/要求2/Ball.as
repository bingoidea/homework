package

{

       import flash.display.Sprite;

      
       public class Ball extends Sprite{

              public function Ball(){

                     init();

              }

              private function init():void{

                     graphics.beginFill(0xff0000);

                     graphics.drawCircle(0, 0, 40);

                     graphics.endFill();

              }

       }

}
