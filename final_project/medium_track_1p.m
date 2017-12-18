close all;
errf1s = importdata('SamplePluginPA10/test_folder/rob_slow/t1/errorLog.txt');
errf95s= importdata('SamplePluginPA10/test_folder/rob_slow/t95/errorLog.txt');
errf90s= importdata('SamplePluginPA10/test_folder/rob_slow/t90/errorLog.txt');
errf85s= importdata('SamplePluginPA10/test_folder/rob_slow/t85/errorLog.txt');
errf80s= importdata('SamplePluginPA10/test_folder/rob_slow/t80/errorLog.txt');
errf75s= importdata('SamplePluginPA10/test_folder/rob_slow/t75/errorLog.txt');
errf70s= importdata('SamplePluginPA10/test_folder/rob_slow/t70/errorLog.txt');
errf65s= importdata('SamplePluginPA10/test_folder/rob_slow/t65/errorLog.txt');
errf60s= importdata('SamplePluginPA10/test_folder/rob_slow/t60/errorLog.txt');
errf55s= importdata('SamplePluginPA10/test_folder/rob_slow/t55/errorLog.txt');
errf50s= importdata('SamplePluginPA10/test_folder/rob_slow/t50/errorLog.txt');
errf45s= importdata('SamplePluginPA10/test_folder/rob_slow/t45/errorLog.txt');
errf40s= importdata('SamplePluginPA10/test_folder/rob_slow/t40/errorLog.txt');
errf35s= importdata('SamplePluginPA10/test_folder/rob_slow/t35/errorLog.txt');
errf30s= importdata('SamplePluginPA10/test_folder/rob_slow/t30/errorLog.txt');
errf25s= importdata('SamplePluginPA10/test_folder/rob_slow/t25/errorLog.txt');
errf20s= importdata('SamplePluginPA10/test_folder/rob_slow/t20/errorLog.txt');
errf15s= importdata('SamplePluginPA10/test_folder/rob_slow/t15/errorLog.txt');
errf10s= importdata('SamplePluginPA10/test_folder/rob_slow/t10/errorLog.txt');
errf05s= importdata('SamplePluginPA10/test_folder/rob_slow/t5/errorLog.txt');
%errVecs =[errf1,errf95,errf90,errf85,errf80,errf75,errf70,errf65,errf60,errf55,errf50,errf45,errf40,errf35,errf30,errf25,errf20,errf15,errf10,errf05]

errf3p1s = importdata('SamplePluginPA10/test_folder/rob_slow/t1/errorLog3P.txt');
errf3p95s= importdata('SamplePluginPA10/test_folder/rob_slow/t95/errorLog3P.txt');
errf3p90s= importdata('SamplePluginPA10/test_folder/rob_slow/t90/errorLog3P.txt');
errf3p85s= importdata('SamplePluginPA10/test_folder/rob_slow/t85/errorLog3P.txt');
errf3p80s= importdata('SamplePluginPA10/test_folder/rob_slow/t80/errorLog3P.txt');
errf3p75s= importdata('SamplePluginPA10/test_folder/rob_slow/t75/errorLog3P.txt');
errf3p70s= importdata('SamplePluginPA10/test_folder/rob_slow/t70/errorLog3P.txt');
errf3p65s= importdata('SamplePluginPA10/test_folder/rob_slow/t65/errorLog3P.txt');
errf3p60s= importdata('SamplePluginPA10/test_folder/rob_slow/t60/errorLog3P.txt');
errf3p55s= importdata('SamplePluginPA10/test_folder/rob_slow/t55/errorLog3P.txt');
errf3p50s= importdata('SamplePluginPA10/test_folder/rob_slow/t50/errorLog3P.txt');
errf3p45s= importdata('SamplePluginPA10/test_folder/rob_slow/t45/errorLog3P.txt');
errf3p40s= importdata('SamplePluginPA10/test_folder/rob_slow/t40/errorLog3P.txt');
errf3p35s= importdata('SamplePluginPA10/test_folder/rob_slow/t35/errorLog3P.txt');
errf3p30s= importdata('SamplePluginPA10/test_folder/rob_slow/t30/errorLog3P.txt');
errf3p25s= importdata('SamplePluginPA10/test_folder/rob_slow/t25/errorLog3P.txt');
errf3p20s= importdata('SamplePluginPA10/test_folder/rob_slow/t20/errorLog3P.txt');
errf3p15s= importdata('SamplePluginPA10/test_folder/rob_slow/t15/errorLog3P.txt');
errf3p10s= importdata('SamplePluginPA10/test_folder/rob_slow/t10/errorLog3P.txt');
errf3p05s= importdata('SamplePluginPA10/test_folder/rob_slow/t5/errorLog3P.txt');



% tracking error medium

errf1 = importdata('SamplePluginPA10/test_folder/rob_medium/t1/errorLog.txt');
errf95= importdata('SamplePluginPA10/test_folder/rob_medium/t95/errorLog.txt');
errf90= importdata('SamplePluginPA10/test_folder/rob_medium/t90/errorLog.txt');
errf85= importdata('SamplePluginPA10/test_folder/rob_medium/t85/errorLog.txt');
errf80= importdata('SamplePluginPA10/test_folder/rob_medium/t80/errorLog.txt');
errf75= importdata('SamplePluginPA10/test_folder/rob_medium/t75/errorLog.txt');
errf70= importdata('SamplePluginPA10/test_folder/rob_medium/t70/errorLog.txt');
errf65= importdata('SamplePluginPA10/test_folder/rob_medium/t65/errorLog.txt');
errf60= importdata('SamplePluginPA10/test_folder/rob_medium/t60/errorLog.txt');
errf55= importdata('SamplePluginPA10/test_folder/rob_medium/t55/errorLog.txt');
errf50= importdata('SamplePluginPA10/test_folder/rob_medium/t50/errorLog.txt');
errf45= importdata('SamplePluginPA10/test_folder/rob_medium/t45/errorLog.txt');
errf40= importdata('SamplePluginPA10/test_folder/rob_medium/t40/errorLog.txt');
errf35= importdata('SamplePluginPA10/test_folder/rob_medium/t35/errorLog.txt');
errf30= importdata('SamplePluginPA10/test_folder/rob_medium/t30/errorLog.txt');
errf25= importdata('SamplePluginPA10/test_folder/rob_medium/t25/errorLog.txt');
errf20= importdata('SamplePluginPA10/test_folder/rob_medium/t20/errorLog.txt');
errf15= importdata('SamplePluginPA10/test_folder/rob_medium/t15/errorLog.txt');
errf10= importdata('SamplePluginPA10/test_folder/rob_medium/t10/errorLog.txt');
errf05= importdata('SamplePluginPA10/test_folder/rob_medium/t5/errorLog.txt');
errVec =[errf1,errf95,errf90,errf85,errf80,errf75,errf70,errf65,errf60,errf55,errf50,errf45,errf40,errf35,errf30,errf25,errf20,errf15,errf10,errf05]

errf3p1 = importdata('SamplePluginPA10/test_folder/rob_medium/t1/errorLog3P.txt');
errf3p95= importdata('SamplePluginPA10/test_folder/rob_medium/t95/errorLog3P.txt');
errf3p90= importdata('SamplePluginPA10/test_folder/rob_medium/t90/errorLog3P.txt');
errf3p85= importdata('SamplePluginPA10/test_folder/rob_medium/t85/errorLog3P.txt');
errf3p80= importdata('SamplePluginPA10/test_folder/rob_medium/t80/errorLog3P.txt');
errf3p75= importdata('SamplePluginPA10/test_folder/rob_medium/t75/errorLog3P.txt');
errf3p70= importdata('SamplePluginPA10/test_folder/rob_medium/t70/errorLog3P.txt');
errf3p65= importdata('SamplePluginPA10/test_folder/rob_medium/t65/errorLog3P.txt');
errf3p60= importdata('SamplePluginPA10/test_folder/rob_medium/t60/errorLog3P.txt');
errf3p55= importdata('SamplePluginPA10/test_folder/rob_medium/t55/errorLog3P.txt');
errf3p50= importdata('SamplePluginPA10/test_folder/rob_medium/t50/errorLog3P.txt');
errf3p45= importdata('SamplePluginPA10/test_folder/rob_medium/t45/errorLog3P.txt');
errf3p40= importdata('SamplePluginPA10/test_folder/rob_medium/t40/errorLog3P.txt');
errf3p35= importdata('SamplePluginPA10/test_folder/rob_medium/t35/errorLog3P.txt');
errf3p30= importdata('SamplePluginPA10/test_folder/rob_medium/t30/errorLog3P.txt');
errf3p25= importdata('SamplePluginPA10/test_folder/rob_medium/t25/errorLog3P.txt');
errf3p20= importdata('SamplePluginPA10/test_folder/rob_medium/t20/errorLog3P.txt');
errf3p15= importdata('SamplePluginPA10/test_folder/rob_medium/t15/errorLog3P.txt');
errf3p10= importdata('SamplePluginPA10/test_folder/rob_medium/t10/errorLog3P.txt');
errf3p05= importdata('SamplePluginPA10/test_folder/rob_medium/t5/errorLog3P.txt');

%timeVec =[1 , .95,.9,.85,.8,.75,.7,.65,.6,.55,.5,.45,.40,.35,.3,.25,.2,.15,.1,.05]

%plot(timeVec,errVec)
%title('Tracking error in Euclidean distance in pixel for different dt')
%xlabel('dt')
%ylabel('maximum error in pixels')
%legend('slow 1p','slow 3p','medium 1p','medium 3p','fast 1p','fast 3p')
%%
% track error fast
errf1f = importdata('SamplePluginPA10/test_folder/rob_fast/t1/errorLog.txt');
errf95f= importdata('SamplePluginPA10/test_folder/rob_fast/t95/errorLog.txt');
errf90f= importdata('SamplePluginPA10/test_folder/rob_fast/t90/errorLog.txt');
errf85f= importdata('SamplePluginPA10/test_folder/rob_fast/t85/errorLog.txt');
errf80f= importdata('SamplePluginPA10/test_folder/rob_fast/t80/errorLog.txt');
errf75f= importdata('SamplePluginPA10/test_folder/rob_fast/t75/errorLog.txt');
errf70f= importdata('SamplePluginPA10/test_folder/rob_fast/t70/errorLog.txt');
errf65f= importdata('SamplePluginPA10/test_folder/rob_fast/t65/errorLog.txt');
errf60f= importdata('SamplePluginPA10/test_folder/rob_fast/t60/errorLog.txt');
errf55f= importdata('SamplePluginPA10/test_folder/rob_fast/t55/errorLog.txt');
errf50f= importdata('SamplePluginPA10/test_folder/rob_fast/t50/errorLog.txt');
errf45f= importdata('SamplePluginPA10/test_folder/rob_fast/t45/errorLog.txt');
errf40f= importdata('SamplePluginPA10/test_folder/rob_fast/t40/errorLog.txt');
errf35f= importdata('SamplePluginPA10/test_folder/rob_fast/t35/errorLog.txt');
errf30f= importdata('SamplePluginPA10/test_folder/rob_fast/t30/errorLog.txt');
errf25f= importdata('SamplePluginPA10/test_folder/rob_fast/t25/errorLog.txt');
errf20f= importdata('SamplePluginPA10/test_folder/rob_fast/t20/errorLog.txt');
errf15f= importdata('SamplePluginPA10/test_folder/rob_fast/t15/errorLog.txt');
errf10f= importdata('SamplePluginPA10/test_folder/rob_fast/t10/errorLog.txt');
errf05f= importdata('SamplePluginPA10/test_folder/rob_fast/t5/errorLog.txt');
errVecf =[errf1f,errf95f,errf90f,errf85f,errf80f,errf75f,errf70f,errf65f,errf60f,errf55f,errf50f,errf45f,errf40f,errf35f,errf30f,errf25f,errf20f,errf15f,errf10f,errf05f]

errf3p1f = importdata('SamplePluginPA10/test_folder/rob_fast/t1/errorLog3P.txt');
errf3p95f= importdata('SamplePluginPA10/test_folder/rob_fast/t95/errorLog3P.txt');
errf3p90f= importdata('SamplePluginPA10/test_folder/rob_fast/t90/errorLog3P.txt');
errf3p85f= importdata('SamplePluginPA10/test_folder/rob_fast/t85/errorLog3P.txt');
errf3p80f= importdata('SamplePluginPA10/test_folder/rob_fast/t80/errorLog3P.txt');
errf3p75f= importdata('SamplePluginPA10/test_folder/rob_fast/t75/errorLog3P.txt');
errf3p70f= importdata('SamplePluginPA10/test_folder/rob_fast/t70/errorLog3P.txt');
errf3p65f= importdata('SamplePluginPA10/test_folder/rob_fast/t65/errorLog3P.txt');
errf3p60f= importdata('SamplePluginPA10/test_folder/rob_fast/t60/errorLog3P.txt');
errf3p55f= importdata('SamplePluginPA10/test_folder/rob_fast/t55/errorLog3P.txt');
errf3p50f= importdata('SamplePluginPA10/test_folder/rob_fast/t50/errorLog3P.txt');
errf3p45f= importdata('SamplePluginPA10/test_folder/rob_fast/t45/errorLog3P.txt');
errf3p40f= importdata('SamplePluginPA10/test_folder/rob_fast/t40/errorLog3P.txt');
errf3p35f= importdata('SamplePluginPA10/test_folder/rob_fast/t35/errorLog3P.txt');
errf3p30f= importdata('SamplePluginPA10/test_folder/rob_fast/t30/errorLog3P.txt');
errf3p25f= importdata('SamplePluginPA10/test_folder/rob_fast/t25/errorLog3P.txt');
errf3p20f= importdata('SamplePluginPA10/test_folder/rob_fast/t20/errorLog3P.txt');
errf3p15f= importdata('SamplePluginPA10/test_folder/rob_fast/t15/errorLog3P.txt');
errf3p10f= importdata('SamplePluginPA10/test_folder/rob_fast/t10/errorLog3P.txt');
errf3p05f= importdata('SamplePluginPA10/test_folder/rob_fast/t5/errorLog3P.txt');

errVec3pf =[errf3p1f,errf3p95f,errf3p90f,errf3p85f,errf3p80f,errf3p75f,errf3p70f,errf3p65f,errf3p60f,errf3p55f,errf3p50f,errf3p45f,errf3p40f,errf3p35f,errf3p30f,errf3p25f,errf3p20f,errf3p15f,errf3p10f,errf3p05f]

%timeVec =[1 , .95,.9,.85,.8,.75,.7,.65,.6,.55,.5,.45,.40,.35,.3,.25,.2,.15,.1,.05]

plot(timeVec, errVec3pf)
title('Tracking error in Euclidean distance in pixel for different dt in fast marker positions')
xlabel('dt')
ylabel('maximum error in pixels')
%legend('slow 1p','slow 3p','medium 1p','medium 3p','fast 1p','fast 3p')
