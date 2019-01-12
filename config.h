/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char bg[]          = "#000000";
static const char fg[]          = "#ffffff";
static const char bg_sel[]      = "#666666";
static const char fg_sel[]      = "#ffffff";
static const char border[]       = "#bbbbbb";
static const char border_focus[] = "#aa0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg,        bg,        border },
	[SchemeSel]  = { fg_sel,    bg_sel,    border_focus  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Google-chrome",  NULL, NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	//{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // "Windows key"
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *dmenu_favs[] =  { "dmenu_favs", NULL }; 
static const char *dmenu_cmd[] =   { "dmenu_run", NULL }; 
static const char *dmenu_rs[] =    { "dmenu_rs", NULL };
static const char *dmenu_uni[] =    { "dmenu_uni", NULL };
static const char *dmenu_emoji[] =  { "dmenu_uni", "emoji", NULL };
static const char *findcursor[] = { "find-cursor", NULL };

static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] =    { "st", "-t", scratchpadname, NULL };

static const char *brightness_up[]  =   { "wm-brightness", "up",      NULL };
static const char *brightness_down[]  = { "wm-brightness", "down",    NULL };
static const char *volume_up[] =        { "wm-volume",     "up",      NULL };
static const char *volume_down[] =      { "wm-volume",     "down",    NULL };
static const char *volume_mute[] =      { "wm-volume",     "mute",    NULL };
static const char *volume_micmute[] =   { "wm-volume",     "micmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* Launching programs */
	{ MODKEY,                       XK_r,      spawn,             {.v = dmenu_favs } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,             {.v = dmenu_cmd } },
	{ MODKEY,                       XK_e,      spawn,             {.v = dmenu_rs } },
	{ MODKEY,                       XK_u,      spawn,             {.v = dmenu_uni } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,             {.v = dmenu_emoji } },

	{ MODKEY,                       XK_x,      spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_backslash, togglescratch,  {.v = scratchpadcmd } },
	{ 0,                            XK_KP_Add, spawn,             {.v = findcursor } },

	{ 0,                            XF86XK_MonBrightnessUp,   spawn, {.v = brightness_up } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v = brightness_down } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn, {.v = volume_up } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn, {.v = volume_down } },
	{ 0,                            XF86XK_AudioMute,         spawn, {.v = volume_mute } },
	{ 0,                            XF86XK_AudioMicMute,      spawn, {.v = volume_micmute } },

	/* Move windows */
	{ MODKEY,                       XK_Left,   edgemove,       {.v = "left" } },
	{ MODKEY,                       XK_Right,  edgemove,       {.v = "right" } },
	{ MODKEY,                       XK_Up,     edgemove,       {.v = "top" } },
	{ MODKEY,                       XK_Down,   edgemove,       {.v = "bottom" } },
	{ MODKEY,                       XK_m,      togglemaximize, {0} },

	/* Show only tagged */
	{ MODKEY,                       XK_F1,     view,           {.ui = 1<<0 } },
	{ MODKEY,                       XK_F2,     view,           {.ui = 1<<1 } },
	{ MODKEY,                       XK_F3,     view,           {.ui = 1<<2 } },
	{ MODKEY,                       XK_F4,     view,           {.ui = 1<<3 } },
	{ MODKEY,                       XK_F5,     view,           {.ui = 1<<4 } },
	/* Apply only this tag */
	{ MODKEY,                       XK_1,      tag,            {.ui = 1<<0 } },
	{ MODKEY,                       XK_2,      tag,            {.ui = 1<<1 } },
	{ MODKEY,                       XK_3,      tag,            {.ui = 1<<2 } },
	{ MODKEY,                       XK_4,      tag,            {.ui = 1<<3 } },
	{ MODKEY,                       XK_5,      tag,            {.ui = 1<<4 } },

	/* Focus next/prev windows */
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	/* Toggle window between tiled and floating */
	{ MODKEY,                       XK_space,  togglefloating, {0} },

	/* Increase/decreate number of windows in master area */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* Increase/decreate master area size */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* Zooms/cycles focused window to/from master area  (tiled  layouts only) */
	{ MODKEY,                       XK_Return, zoom,           {0} },

	/* Kill windows */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	/* Quit dwm */
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
