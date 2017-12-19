void edgemove(const Arg *arg) {
	XEvent ev;
	Monitor *m = selmon;

	if (!(m->sel && arg && arg->v && m->sel->isfloating))
		return;

	char *dir = (char *)arg->v;
	int x = m->sel->x;
	int y = m->sel->y;
	size_t s = sizeof(s);

	if (strncmp(dir, "left", s) == 0)
		x = 0;
	else if (strncmp(dir, "right", s) == 0)
		x = m->ww - m->sel->w - (m->sel->bw*2);
	else if (strncmp(dir, "top", s) == 0)
		y = 0;
	else if (strncmp(dir, "bottom", s) == 0)
		y = m->wh - m->sel->h - (m->sel->bw*2);
	else
		return;

	resize(m->sel, x, y,
	       m->sel->w, m->sel->h,
	       True);

	while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}
