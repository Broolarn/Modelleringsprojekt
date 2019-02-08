function [] = Roteuler(speltid,lamda,starthastighet,snurra,rotationdirection)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

i=1;
w(i)=starthastighet;
h=1/60;

for t = h:h:speltid
    w(i+1) = w(i) + h*lamda*w(i);  %rotspeed
   % Rotmatrix=[(w(i+1)-w(i))/h,-(w(i+1)-w(i))/h,0;(w(i+1)-w(i))/h,(w(i+1)-w(i))/h,0;0,0,1];    
    %w(i+1)
    rotate(snurra,rotationdirection,w(i))
    pause(1/60)
    i = i+1;
end

end

