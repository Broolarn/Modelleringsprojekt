function [s,v] = Translationeuler(speltid,lamda,starthastighet,bx,by,bz)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
i=1;
s(i)=0;
v(i)=starthastighet;
%Transmatrix=zeros(4,4);
%hpos=[1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1]; 
h=1/60;

for  t2=h:h:speltid
    
        s(i+1)= s(i) + h*v(i);
        v(i+1) = v(i) + h*lamda*v(i); %transspeed
       axis vis3d
       shading flat
       %Använd denna kamera vy när du ska köra plan translation.
      %   campos([0.25,-0.5,0.4])
      %Använd denna kamera vy när du ska köra lutande plan translation.
           campos([3,-6,-1])
        hold on
        surf(bx+s(i),by+s(i),bz,'FaceAlpha',0.25)
      
        pause(1/60)
    i = i+1;
    
end




end

