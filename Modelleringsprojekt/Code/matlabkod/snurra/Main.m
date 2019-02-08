%% Main
clear all
%bladespecifikaitoner
m=0.024; %snurrans massa
radie=0.025;%snurrans radie
hojd=0.05;%snurrans höjd

%snurrans skapelse
[bx,by,bz]=sphere;
bx = bx*radie;
by=by*radie;
bz= bz*radie;
snurra=surf(bx,by,bz);%surf(peaks(20));

%% setup för loopar
h=1/60; %steglängden
t_final = 560; % körtid på rotation
tt = 2; % körtid på translation
%konstanter för stegmetod
b=0.0002; %frikstionskonstant rotation
my=0.2;
airmy=1.846;
theta=20*pi/180;
g=9.82;
%uttryck för lamnda
rotlamda=rotlamda(m,radie,b,hojd,airmy);
translamda = -(my/m);
lutandelamda = m*g*(1-cos(theta));
%rotations axeln kring vilken snurran roterar runt
rotationdirection=[0 0 1];
% Snurra start fart
w(1) = 271 ; % 4500RPM rotation
v(1) = 0.2; % 0.2 m/s translation

%% Rotation
Roteuler(t_final,rotlamda,w(1),snurra,rotationdirection)

%% Translation
[s,v]=Translationeuler(tt,translamda,v(1),bx,by,bz);
figure
t2=0:h:tt;
ax=subplot(2,1,1)
plot(ax,t2,v)
ax2=subplot(2,1,2)
plot(ax2,t2,s)

%% Lutande plan
[s,v]=Translationeuler(tt,lutandelamda,v(1),bx,by,bz);
figure
t2=0:h:tt;
ax=subplot(2,1,1)
plot(ax,t2,v)
ax2=subplot(2,1,2)
plot(ax2,t2,s)

%% half pipe
pause(3)
close all
phiv=0; %starthastighet för rotation rörelsen-> pendel ish
tt=3;
b=0.02;%sätt till 0.0002för pendelrörelse. 
Sphericaleuler(m,phiv,tt,b,radie,bx,by,bz)

%% Sfärbana
pause(3)
close all
phiv=2; % starthastighet för rotation rörelsen
tt=3;
b=0.02;%friktionskoefficient för plast på plast
Sphericaleuler(m,phiv,tt,b,radie,bx,by,bz)
