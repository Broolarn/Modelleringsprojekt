function [] = Sphericaleuler(m,phiv,tt,b,radie,bx,by,bz)
%index       
i=1;
%starvalues and constants
w(i)=0;
v(i)=0;
a(i)=0;
h=1/60;
r=0.2;
g=9.82;
phiv(i)=phiv;
%startpos
xpos(i)=r-radie;
ypos(i)=r-radie;
zpos(i)=0.1;
%startangles
phi(i)=xpos(i)/ypos(i);
Theta(i)=xpos(i)/zpos(i);


for  t2=h:h:tt
    phia(i)=phiv(i)/r;
    phiv(i+1) = phiv(i) +h*phia(i);%-(b/m)*phiv(i);  %rotspeed %v- friktion
    phi(i+1)=phi(i)+phiv(i+1)*h;
    
    a(i)=-g*sin(Theta(i))/r;    
    %sin gives radians
     
    w(i+1)=w(i)+a(i)*h -(b/m)*w(i) ;%b/m är motståndet
    Theta(i+1)=Theta(i)+w(i+1)*h; 
    
    X(i)=r*sin(Theta(i))*cos(phi(i)); % polar to cartesian
    Y(i)=r*sin(Theta(i))*sin(phi(i));
    Z(i)=-r*cos(Theta(i));
    
     axis vis3d
    shading flat
    %Använd denna kamera vy när du ska köra Sfärbana.
    campos([0,-4,0])
    %Använd denna kamera vy när du ska köra half-pipe.
    %campos([3,0,0])
    hold on
    hsurf=surf(bx+X(i),by+Y(i),bz+Z(i),'FaceAlpha',0.25);
    rotate(hsurf,[0 1 0],Theta(i))
    rotate(hsurf,[0 0 1],phi(i))
    pause(1/60)
    
    i = i+1;
    
end




end

