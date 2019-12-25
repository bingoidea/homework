function Hough(I)
 subplot(1,3,1);
 imshow(I);
 f=rgb2gray(I);
 g=edge(f,'sobel');
 subplot(1,3,2);
 imshow(g);
 subplot(1,3,3);
 imshow(g);
 [row,col]=size(g);
 pinfang=round((row*row+col*col)^0.5);
 A=zeros(2*pinfang,180);
 
 for m=1:row
     for n=1:col
         if g(m,n)>0
             for thera=1:180
                 r=thera/180*pi;  %角度转弧度
                 rho=round(m*cos(r)+n*sin(r)); %p=cosQ+sinQ
                 rho=rho+pinfang; %-1:1转换到1:2L
                 A(rho,thera)=A(rho,thera)+1;
             end
         end
     end
 end
 [rpo,thepa]=find(A>60); %交点超过60条线的点,rpo, thepa为参数空间的坐标
 nma=length(rpo);
 for i=1:nma
     hold on
     m=1:row;  
     r=thepa(i)/180*pi;
     n=(rpo(i)-pinfang-m*cos(r))/(sin(r));
     plot(n,m,'r');
 end



     