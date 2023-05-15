//max frame-rate
bool end = false;
while(!end)
{
	input();
	logic();
	render();
	delay(N);		//N=16.6  -> 1000/16.6 = 60fps
}
//fixed frame-rate
bool end = false;
while(!end)
{
	t1 = GetTime();
	input();
	logic();
	render();
	do { t2 = GetTime();
	} while(t2-t1 < N);
}
//time syncr
bool end = false;
while(!end)
{
	t1 = GetTime();
	input();
	logic(dt);
	render();
	dt = GetTime() - t1;
}