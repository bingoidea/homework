package

{

	import flash.display.Sprite;

	import flash.events.MouseEvent;


	public class Reparenting extends Sprite {

		//private var parent1: Sprite;
		
		private var parent1: Parent;

		//private var parent2: Sprite;
		
		private var parent2: Parent;

		//private var ball: Sprite;
		
		private var ball: Ball;
		
		private var flag: Boolean;

		public function Reparenting() {

			init();

		}

		private function init(): void {
			
			flag = false;

			//parent1 = new Sprite();
			
			parent1 = new Parent();

			addChild(parent1);

			//parent1.graphics.lineStyle(1, 0);

			//parent1.graphics.drawRect(-50, -50, 100, 100);

			parent1.x = 60;

			parent1.y = 60;


			//parent2 = new Sprite();
			
			parent2 = new Parent();

			addChild(parent2);

			//parent2.graphics.lineStyle(1, 0);

			//parent2.graphics.drawRect(-50, -50, 100, 100);

			parent2.x = 170;

			parent2.y = 60;


			//ball = new Sprite();
			
			ball = new Ball();

			parent1.addChild(ball);

			//ball.graphics.beginFill(0xff0000);

			//ball.graphics.drawCircle(0, 0, 40);

			//ball.graphics.endFill();

			ball.addEventListener(MouseEvent.CLICK, onBallClick);

		}

		private function onBallClick(events: MouseEvent): void {
			
			flag ? parent1.addChild(ball) : parent2.addChild(ball);
			
			flag = !flag;

		}

	}

}