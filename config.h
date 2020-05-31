#include "layouts.c"
#include "movestack.c"
/* See LICENSE file for copyright and license details. */
// #include "push.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int bar_padding        = 4; /* #pixels added to bar font height */
// #include "/home/sander/.dwm/theme.h"
static char dmenufont[]       = "DroidSansMonoNerdFontMono:size=8";
static char col_gray1[]       = "#222222";
static char col_gray2[]       = "#444444";
static char col_gray3[]       = "#bbbbbb";
static char col_gray4[]       = "#eeeeee";
static char col_cyan[]        = "#ee8000";

static const unsigned int baralpha = 0xf0;

static const char *xres = "/home/sander/.Xresources";
// static const char *fonts[] = { dmenufont };
static char *fonts[] = { dmenufont };
static const unsigned int borderalpha = OPAQUE;
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {"st", "-n", "sppython", "-g", "50x20", "-e", "python", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",   spcmd1 },
	{"spcalc",   spcmd2 },
	{"sppython", spcmd3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Surf",     NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Chromium",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,       NULL,       "Mu4e",     1 << 7,       0,           -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spcalc",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "sppython",  	NULL,		SPTAG(2),		1,			 -1 },
 };
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "  ",      tile },    /* first entry is default */
	{ "  ",      monocle },
	{ " T ",      bstack },
	{ " = ",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },

	{ NULL,       NULL },
	/* { " 﩯 ",      grid }, */
	/* { "  ",      NULL },    /\* no layout function means floating behavior *\/ */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
//static const char scratchpadname[] = "scratchpad";
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] =
  {
   /* modifier                     key        function        argument */
    //  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    // { MODKEY,             XK_b,      togglebar,      {0} },
    //   { MODKEY|ShiftMask,   XK_j,      movestack,      {.i = +1 } },
    // { MODKEY|ShiftMask,   XK_k,      movestack,      {.i = -1 } },
    { ControlMask,        XK_grave,  togglescratch,  {.ui = 0 } },
   //   { MODKEY,             XK_j,      focusstack,     {.i = +1 } },
   //   { MODKEY,             XK_k,      focusstack,     {.i = -1 } },
   //  { MODKEY,             XK_period, incnmaster,     {.i = +1 } },
   //  { MODKEY,             XK_comma,  incnmaster,     {.i = -1 } },
   //  { MODKEY,             XK_h,      setmfact,       {.f = -0.05} },
   //  { MODKEY,             XK_l,      setmfact,       {.f = +0.05} },
   //   { MODKEY,	           XK_q,      killclient,     {0} },
   //  { MODKEY,	           XK_space,  zoom,           {0} },
   //  { MODKEY|ShiftMask,   XK_space,  cyclelayout,    {.i = +1 } },
   //  { ControlMask|ShiftMask,   XK_1,      setlayout,      {.v = &layouts[0]} },
   //  { ControlMask|ShiftMask,   XK_2,      setlayout,      {.v = &layouts[1]} },
   //  { ControlMask|ShiftMask,   XK_3,      setlayout,      {.v = &layouts[2]} },
   //  { ControlMask|ShiftMask,   XK_4,      setlayout,      {.v = &layouts[4]} },
   //  { ControlMask|ShiftMask,   XK_5,      setlayout,      {.v = &layouts[5]} },
   //  { MODKEY,             XK_0,      view,           {.ui = ~0 } },
   //  { MODKEY|ShiftMask,   XK_0,      tag,            {.ui = ~0 } },
   //  { MODKEY,             XK_a,      setgaps,        {.i = -1 } },
   //  { MODKEY,             XK_s,      setgaps,        {.i = +1 } },
   // { MODKEY,             XK_F5,     xrdb,           {.v = NULL } },
   TAGKEYS(              XK_1,                      0)
   TAGKEYS(              XK_2,                      1)
   TAGKEYS(              XK_3,                      2)
   TAGKEYS(              XK_4,                      3)
   TAGKEYS(              XK_5,                      4)
   TAGKEYS(              XK_6,                      5)
   TAGKEYS(              XK_7,                      6)
   TAGKEYS(              XK_8,                      7)
   TAGKEYS(              XK_9,                      8)
   //  { MODKEY|ShiftMask,   XK_q,      quit,           {1} },
   //  { MODKEY|ControlMask|ShiftMask, XK_q,      quit, {0} },
   //  { MODKEY,             XK_Tab,   focusmon,       {.i = -1 } },
   //  { MODKEY|ShiftMask,   XK_Tab,   tagmon,         {.i = -1 } },
   /* { MODKEY|ShiftMask,   XK_Right,  tagmon,         {.i = +1 } }, */
   /* { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } }, */
  };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] =
  {
   /* click         event mask button    function        argument */
   { ClkStatusText, 0,      Button2, spawn,          {.v = termcmd } },
   { ClkLtSymbol,   0,      Button1, setlayout,      {0} },
   { ClkLtSymbol,   0,      Button3, setlayout,      {.v = &layouts[2]} },
   { ClkWinTitle,   0,      Button2, zoom,           {0} },
   { ClkClientWin,  MODKEY, Button1, movemouse,      {0} },
   { ClkClientWin,  MODKEY, Button2, togglefloating, {0} },
   { ClkClientWin,  MODKEY, Button3, resizemouse,    {0} },
   { ClkTagBar,     0,      Button1, view,           {0} },
   { ClkTagBar,     0,      Button3, toggleview,     {0} },
   { ClkTagBar,     MODKEY, Button1, tag,            {0} },
   { ClkTagBar,     MODKEY, Button3, toggletag,      {0} },
  };

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

void scratchpad(const Arg *arg)
{
  // togglescratch ( &((Arg){ .v = scratchpadcmd }) );
	togglescratch(&((Arg) { .ui = 1 << arg->ui }));
}
/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "cyclelayout",    cyclelayout },
	{ "focusstack",     focusstack },
	{ "focusmon",       focusmon },
	{ "incnmaster",     incnmaster },
	{ "killclient",     killclient },
  { "scratchpad",     scratchpad },
	{ "movestack",      movestack},
	{ "setgaps",        setgaps },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "setmfact",       setmfact },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "tagmon",         tagmon },
	{ "togglebar",      togglebar },
	{ "togglefloating", togglefloating },
	{ "scratchpad",     scratchpad },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "toggletagex",    toggletagex },
	{ "toggletag",      tag },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "xrdb",           xrdb },
	{ "quit",           quit },
	{ "zoom",           zoom },
};

