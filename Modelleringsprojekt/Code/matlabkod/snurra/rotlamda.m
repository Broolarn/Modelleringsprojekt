function [lamda] = rotlamda(m,radie,b,hojd,airmy)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

M=(3/10)*m*radie^2;
Mb=b/m;
Mluft=2*pi*airmy*radie*hojd/3;

lamda=(M-Mb-Mluft);
end

