	package

{

	import flash.display.Sprite;

	import flash.events.MouseEvent;
	import flash.events.Event;


	public class Reparenting extends Sprite {
		
		private var parent1: Parent;
		
		private var parent2: Parent;
		
		private var ball: Ball;
		
		private var flag: Boolean;

		public function Reparenting() {

			init();

		}

		private function init(): void {
			
			stage.frameRate = 3; // 帧速度
			
			flag = false;
			
			
			parent1 = new Parent();

			addChild(parent1);

			parent1.x = 60;

			parent1.y = 60;
			
			
			parent2 = new Parent();

			addChild(parent2);

			parent2.x = 170;

			parent2.y = 60;
			
			
			ball = new Ball();

			parent1.addChild(ball);

			ball.addEventListener(Event.ENTER_FRAME, onBallClick);

		}

		private function onBallClick(e:Event): void {
			
			flag ? parent1.addChild(ball) : parent2.addChild(ball);
			
			flag = !flag;

		}

	}

}