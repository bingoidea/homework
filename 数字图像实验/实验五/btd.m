%������˹��ͨƵ���˲�
I=imread('D:\��ѧ\����ͼ����\ʵ��\2019ʵ�鰲��\ʵ����\lena.jpg');
subplot(2,3,1),imshow(I),title('ԭʼͼ��');
J1=imnoise(I,'gaussian',0,0.02);
      %��ͼ��������Ӿ�ֵΪ0������Ϊ0.02�ĸ�˹������
J2=imnoise(I,'salt & pepper',0.02);
      %��ͼ��������ӽ���������
subplot(2,3,2);
imshow(J1);
title('�����˹����������ͼ��');
subplot(2,3,3);
imshow(J2);
title('���뽷�ΰ���������ͼ��');
%F=double(I);                % ��������ת����MATLAB��֧��ͼ����޷������͵ļ���
G1=fft2(J1);                    % ����Ҷ�任
G2=fft2(J2);
G1=fftshift(G1);                 % ת�����ݾ���
G2=fftshift(G2);
[M,N]=size(G1);
nn=2;                       % ���װ�����˹(Butterworth)��ͨ�˲���
d0=30;                      %��ֹƵ��Ϊ30
m=fix(M/2); n=fix(N/2);
for i=1:M
       for j=1:N
           d=sqrt((i-m)^2+(j-n)^2);
           h=1/(1+1*(d/d0)^(2*nn));         % �����ͨ�˲������ݺ���
           result1(i,j)=h*G1(i,j);
           result2(i,j)=h*G2(i,j);
       end
end
result1=ifftshift(result1);
result2=ifftshift(result2);
Y1=ifft2(result1);
Y2=ifft2(result2);
Y3=uint8(Y1);
Y4=uint8(Y2);
subplot(2,3,4),imshow(Y3),title('������˹��ͨ�˲���˹����ͼ��');
subplot(2,3,5),imshow(Y4),title('������˹��ͨ�˲���������ͼ��');