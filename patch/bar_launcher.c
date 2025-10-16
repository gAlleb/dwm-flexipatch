#if BAR_STATUS2D_PATCH
int
width_launcher(Bar *bar, BarArg *a)
{
	int i, x = 0;
	char formatted_name[256]; /* Buffer to hold the formatted string */

	for (i = 0; i < LENGTH(launchers); i++) {
		/* Format the string to include the color from the Xresources variable
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^^b%s^%s^d^", tagsselfgcolor, tagsselbgcolor, launchers[i].name);
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^%s^d^", tagsselbgcolor, launchers[i].name); */
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^^b%s^%s^d^", tagsselfgcolor, tagsselbgcolor, launchers[i].name);
		/* status2dtextlength is smart enough to ignore the color codes for width calculation */
    /* Add padding to the right */
    /* x += status2dtextlength(formatted_name) + lrpad; */
    x += status2dtextlength(formatted_name);
	}
	return x;
}

int
draw_launcher(Bar *bar, BarArg *a)
{
	int i, w = 0;
	char formatted_name[256]; /* Buffer to hold the formatted string */

	for (i = 0; i < LENGTH(launchers); i++) {
		/* Format the string just like we did for the width calculation 
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^^b%s^%s^d^", tagsselfgcolor, tagsselbgcolor, launchers[i].name); 
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^%s^d^", tagsselbgcolor, launchers[i].name); */
    snprintf(formatted_name, sizeof(formatted_name), "^c%s^^b%s^%s^d^", tagsselfgcolor, tagsselbgcolor, launchers[i].name); 
		w = status2dtextlength(formatted_name);
		/* Draw the newly formatted string instead of the original one */
		drawstatusbar(a, formatted_name);
		a->x += w + lrpad;
	}

	return a->x;
}

int
click_launcher(Bar *bar, Arg *arg, BarArg *a)
{
	int i, x = 0;

	for (i = 0; i < LENGTH(launchers); i++) {
    /* Add padding to the right */
    /* x += status2dtextlength(launchers[i].name) + lrpad; */
    x += status2dtextlength(launchers[i].name);
		if (a->x < x) {
		    spawn(&launchers[i].command);
		    break;
		}
	}
	return -1;
}
#else
int
width_launcher(Bar *bar, BarArg *a)
{
	int i, x = 0;

	for (i = 0; i < LENGTH(launchers); i++) {
		x += TEXTW(launchers[i].name);
	}
	return x;
}

int
draw_launcher(Bar *bar, BarArg *a)
{
	int i, x = 0, w = 0;;

	for (i = 0; i < LENGTH(launchers); i++) {
		w = TEXTW(launchers[i].name);
		drw_text(drw, x, 0, w, bh, lrpad / 2, launchers[i].name, 0, True);
		x += w;
	}

	return x;
}

int
click_launcher(Bar *bar, Arg *arg, BarArg *a)
{
	int i, x = 0;

	for (i = 0; i < LENGTH(launchers); i++) {
		x += TEXTW(launchers[i].name);
		if (a->x < x) {
		    spawn(&launchers[i].command);
		    break;
		}
	}
	return -1;
}
#endif // BAR_STATUS2D_PATCH
