/*
	LOGIC：
	汉诺塔，把所有的碟片A柱子移动到C柱子，大的不能再小的上面
*/

package {
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.ui.Mouse;
	
	public class Main extends MovieClip {
		// 常量
		var totalDisk:int = 4;  // 总碟片数         
		var Width:int = 50;     // 最顶上的碟片大小（即最小的那个）
		
		// 变量
		var currDisk:int = -1;  // 当前被拿起来的碟片，一开始的时候没有碟片被拿起
		var widthDiff:Number;   // 每两个碟片之间的宽度差距
		var steps:int;          // 移动的步数
		var lastRod:String;		// 当前碟片最后一个弹出的柱子
		
		// 数组 
		var rodA:Array = new Array();	// 表示柱子A的所有碟片
		var rodB:Array = new Array();	// 表示柱子B的所有碟片
		var rodC:Array = new Array();	// 表示柱子C的所有碟片
		var rodW:Array = new Array();	// 代表最后正确的碟片排序
		var disks:Array = new Array();	// 储存所有碟片的数组，不管碟片在哪个柱子

		
		public function Main(){
			gotoAndStop(1); // 开始界面

			simple.label = "simple";
			normal.label = "normal";
			difficult.label = "difficult";
			simple.addEventListener(MouseEvent.CLICK,level);
			normal.addEventListener(MouseEvent.CLICK,level);
			difficult.addEventListener(MouseEvent.CLICK,level);
			simple.color = 0x7e5414;
			begin.addEventListener(MouseEvent.CLICK,changeFrame2);
			restart.addEventListener(MouseEvent.CLICK,changeFrame1);
			//stage.addEventListener(MouseEvent.MOUSE_UP,onMouseClicked); //If mouse is clicked then onMouseClicked function will be called
			//createDisks()
		}
		
		function level(event:MouseEvent):void {
			if(event.currentTarget.label == "simple") {
				totalDisk = 4;
				trace(totalDisk);
			}
			if(event.currentTarget.label == "normal") {
				totalDisk = 6;
				trace(totalDisk);
			}
			if(event.currentTarget.label == "difficult") {
				totalDisk = 8;
				trace(totalDisk);
			}
			gotoAndStop(2);
			stage.addEventListener(MouseEvent.MOUSE_UP,onMouseClicked); //If mouse is clicked then onMouseClicked function will be called
			createDisks();
		}
		
		// 开始游戏
		function changeFrame2(event:MouseEvent):void {
			gotoAndStop(2);
			stage.addEventListener(MouseEvent.MOUSE_UP,onMouseClicked); //If mouse is clicked then onMouseClicked function will be called
			createDisks();
			//var obj:Object = event.currentTarget;
			//if(obj.currentFrame == 1) {
			//	gotoAndStop(2);
			//	stage.addEventListener(MouseEvent.MOUSE_UP,onMouseClicked); //If mouse is clicked then onMouseClicked function will be called
			//	createDisks();
			//}
		}
		
		// 重新开始
		function changeFrame1(event:MouseEvent):void {
			totalDisk = 4;
			while(disks.length) {
				removeChild(disks.pop());
			}
			currDisk = -1;
			widthDiff = 0;
			steps = 0;
			rodA.splice(0,rodA.length);
			rodB.splice(0,rodB.length);
			rodC.splice(0,rodC.length);
			rodW.splice(0,rodW.length);
			disks.splice(0,disks.length);
			
			gotoAndStop(1);
			simple.label = "simple";
			normal.label = "normal";
			difficult.label = "difficult";
			begin.addEventListener(MouseEvent.CLICK,changeFrame2);
			simple.addEventListener(MouseEvent.CLICK,level);
			normal.addEventListener(MouseEvent.CLICK,level);
			difficult.addEventListener(MouseEvent.CLICK,level);
		}
		
		
		
		// 创建所有碟片
		function createDisks():void {
			//trace(totalDisk);
			msgLbl.visible = false; 
			mcRodA.visible = true;
			mcRodB.visible = true;
			mcRodC.visible = true;

			widthDiff = (mcRodA.width - Width) / totalDisk;		// 计算widthDiff
			for(var i:int = totalDisk - 1; i >= 0 ; --i){		// 从大到小创建碟片
				rodA.push(i);                                	// 存入A柱子
				var tmpDisk:mcDisk = new mcDisk();
				addChild(tmpDisk);								// 把碟片加到舞台上，设置名字，位置和宽度
				tmpDisk.name = i.toString();
				tmpDisk.x = mcRodA.x;
				tmpDisk.y = mcRodA.y  - (rodA.length*tmpDisk.height);
				tmpDisk.width = Width + (i*widthDiff);
				disks.push(tmpDisk);						    // 存到disks数组中
			}
			rodW = rodA.slice();								// 复制到rodW数组中                        
		}
		
		// 当鼠标单击时调用此函数
		function onMouseClicked(event:MouseEvent):void{
			var tmpRod:String;
			// 如果还没有任何碟片被拿起
			if(currDisk == -1){
			    if(0<mouseX && mouseX<=175){  // 在柱子A的范围内且柱子A非空
					tmpRod = "A";
					if(rodA.length != 0){
						currDisk = rodA.pop();
					}
				}else if(175<=mouseX && mouseX<=360){  //在柱子B的范围内且柱子B非空
					tmpRod = "B";
					if(rodB.length != 0){
						currDisk = rodB.pop();
					}
				}else if(360<mouseX && mouseX<=550){	// 在柱子C的范围内且柱子C非空
					tmpRod = "C";
					if(rodC.length != 0){
						 currDisk = rodC.pop();
					}
				}
				lastRod = tmpRod; 				// 最后一个操作过的柱子
				DragDisk(currDisk,tmpRod,true); // 把碟片拿起来
			}
			// 如果已经有碟片被拿起
			else if(currDisk != -1){
				var pushed:Boolean;
				var topDisk:int;
				// 如果任意碟片被拿起，则放置到最近的一个柱子上
				if(0<mouseX && mouseX<=175){	// 如果A柱子最上面的碟片大于当前拿起的柱子，则可以放下
					tmpRod = "A";
					if(rodA.length != 0) {
						topDisk = rodA[rodA.length - 1];
						if(topDisk > currDisk){
							rodA.push(currDisk);
							pushed = true;
						}
					}else{
						rodA.push(currDisk);
						pushed = true;
					}
				}else if(175<mouseX && mouseX<=360){	// 如果B柱子最上面的碟片大于当前拿起的柱子，则可以放下
					tmpRod = "B";
					if(rodB.length != 0) {
						topDisk = rodB[rodB.length - 1];
						if(topDisk > currDisk){
							rodB.push(currDisk);
							pushed = true;
						}
					}else{
						rodB.push(currDisk);
						pushed = true;
					}
				}else if(360<mouseX && mouseX<=550){	// 如果C柱子最上面的碟片大于当前拿起的柱子，则可以放下
					tmpRod = "C";
					if(rodC.length != 0) {
						topDisk = rodC[rodC.length - 1];
						if(topDisk > currDisk){
							rodC.push(currDisk);
							pushed = true;
						}
					}else{
						rodC.push(currDisk);
						pushed = true;
					}
				}
				// 如果一个碟片被放下
				if(pushed){
					DragDisk(currDisk,tmpRod,false);	// 停止拿起
				    currDisk = -1;						// 放下后，把currDisk重置为-1
					
				    if(tmpRod != lastRod){	// 如果放下的柱子和拿起时的柱子不一样，步数+1
					    ++steps;
				    }
				    stepsLbl.text = steps.toString();	// 显示步数
				}
				
				// 游戏结束
				if(checkSolved(rodW)){
					msgLbl.visible = true;
					stage.removeEventListener(MouseEvent.MOUSE_UP,onMouseClicked);
				}
			}
		}
		
		// 此函数将根据参数值来决定拖动还是放下碟片
		function DragDisk(Disk:int,Rod:String,Drag:Boolean) {
			for(var i:int = 0; i<disks.length; ++i) {  // 循环获取碟片
				var tmpDisk = disks[i];
				if(tmpDisk.name == Disk.toString()){
					if(Drag == true){				   // 如果拖动标志为true
						tmpDisk.startDrag(true);
				    }else{							   // 如果拖动标志为false
						var RodLength:int;			   // 计算 RodLength 以把碟片放到正确位置
						if(Rod == "A"){        
							RodLength = rodA.length;
						}else if(Rod == "B"){
							RodLength = rodB.length;
						}else if(Rod == "C"){
							RodLength = rodC.length;
						}
						tmpDisk.x = this["mcRod" + Rod].x;
				    	tmpDisk.y = this["mcRod" + Rod].y  - (RodLength*tmpDisk.height);
						tmpDisk.stopDrag();
				    }
				}
			}
		}
		
		// 游戏结束
		function checkSolved(rodW:Array){
			if(rodW.length != rodC.length){		// 数组rodC的长度不等于rodW的长度
				return false;
			}else{
				for(var i:int = rodW.length - 1; i>=0;--i){ // 数组rodC的长度等于rodW的长度，但两个数组内容不同
					if(rodW[i] != rodC[i])
					return false;
				}
				return true;
			}
		}
	}
}