clear
clc
%total_mine = 10:1:240;
total_location = 16 * 16;
p_a_result=[];
p_b_result=[];
p_c_result=[];
range=10:1:240;
for total_mine=10:1:240
c_m_n_2=1;
%c_m_n_2=nchoosek(total_location - 15, total_mine - 2);
c_m_n_3=(total_location-total_mine-12)/(total_mine-2)*c_m_n_2;
total_count = c_m_n_2*3*5 + c_m_n_3*5*10;
p_a = c_m_n_3 * 10/total_count;
p_b = c_m_n_2 * 5/total_count;
p_c = (c_m_n_2 * 3+c_m_n_3*5*4)/total_count;
p_a_result=[p_a_result,p_a];
p_b_result=[p_b_result,p_b];
p_c_result=[p_c_result,p_c];
end
plot(range,p_a_result,'r')
hold on
plot(range,p_b_result,'g')
hold on
plot(range,p_c_result,'b')