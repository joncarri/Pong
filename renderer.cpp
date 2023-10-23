void render_background()
{
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = 0xff5500;
		}
	}
}

void clear_screen(unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = color;
		}
	}
}

void draw_rect(int x0, int y0,int x1,int y1,unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render_state.memory+x0+y*render_state.width;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = color;
		}
	}
}