/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
// static const char *fonts[]          = { "CaskaydiaCoveNerdFont:size=9:style=bold" };
static const char *fonts[]          = { "MesloLGS Nerd Font:size=18" };
static const char unsel_bg[]        = "#000000";
static const char unsel_fg[]        = "#ffffff";
static const char unsel_border[]        = "#000000";
static const char sel_bg[]        = "#4287f5";
static const char sel_fg[]        = "#000000";
static const char sel_border[]        = "#ffffff";
static const char sel_tag[]        = "#4287f5";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { unsel_fg, unsel_bg, unsel_border },
	[SchemeSel]  = { sel_fg, sel_bg, sel_border },
	[SchemeStatus]  = { unsel_fg, unsel_bg, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { sel_fg, sel_tag, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { unsel_fg, unsel_bg, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { unsel_fg, unsel_bg, "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { unsel_fg, unsel_bg, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"picom", "-b", NULL,
    "sh", "-c", "~/.local/bin/scripts/autostart.sh", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ ".gimp-2.10-wrapped_",     NULL,       NULL,       1 << 4,            0,           -1 },
	{ "Google-chrome",     NULL,       NULL,       1 << 1,            0,           -1 },
};

/* window following */
#define WFACTIVE '>'
#define WFINACTIVE 'v'
#define WFDEFAULT WFACTIVE

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

 static const Layout layouts[] = {
 	/* symbol     arrange function */
 	{ "[]=",      tile },    /* first entry is default */
 	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/env", "bash", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "ghostty", NULL };
// static const char *termcmd[]  = { "~/.local/bin/scripts/alacritty.sh", NULL };
// static const char *flamecmd[]  = { "flameshot", "gui", "-c", "-p", "/home/aaronshahriari/Pictures/Screenshots/", NULL };

#include "movestack.c"
#include "unfloat.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,             spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_a,             spawn,          SHCMD("~/.local/bin/scripts/audio-sessionizer.sh") },
	{ MODKEY,                       XK_Return,        spawn,          {.v = termcmd } },
    { MODKEY,			            XK_c,             spawn,          SHCMD("~/.local/bin/scripts/fix-devices.sh") },
    { MODKEY|ShiftMask,			    XK_s,             spawn,          SHCMD("~/.local/bin/scripts/flameshot-screenshot.sh") },
	{ MODKEY|ShiftMask,             XK_d,             spawn,          SHCMD("~/.local/bin/scripts/display-sessionizer.sh dmenu -m 0 -c") },
	{ MODKEY|ShiftMask,             XK_e,             spawn,          SHCMD("~/.local/bin/scripts/device-sessionizer.sh dmenu -m 0 -c") },
	{ MODKEY,                       XK_g,             spawn,          SHCMD("~/.local/bin/scripts/dmenu-search.sh dmenu -m 0 -c") },
    { MODKEY,			            XK_minus,         spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -35 $(pidof dwmblocks)") },
    { MODKEY,			            XK_equal,         spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -35 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,		        XK_m,             spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -35 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,			    XK_minus,         spawn,          SHCMD("~/.local/bin/scripts/dec_brightness.sh") },
    { MODKEY|ShiftMask,			    XK_equal,         spawn,          SHCMD("~/.local/bin/scripts/inc_brightness.sh") },
    { MODKEY,			            XF86XK_AudioPlay, spawn,          SHCMD("~/.local/bin/scripts/dwmblocks/music/keyboard/play-pause.sh") },
    { MODKEY,			            XF86XK_AudioNext, spawn,          SHCMD("playerctl next") },
    { MODKEY|ShiftMask,			    XF86XK_AudioNext, spawn,          SHCMD("playerctl previous") },
    { MODKEY,                       XK_b,             togglebar,      {0} },
	{ MODKEY,                       XK_j,             focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,             focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_x,             incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_v,             incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_period,        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_comma,         setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_period,        setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_j,             movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,             movestack,      {.i = -1 } },
    { MODKEY,                       XK_r,             resetlayout,    {0} },
	{ MODKEY,                       XK_s,             zoom,           {0} },
	{ MODKEY,                       XK_Tab,           view,           {0} },
	{ MODKEY,                       XK_q,             killclient,     {0} },
	{ MODKEY,                       XK_t,             setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,             setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,             setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,         setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,         togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_t,             unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,             tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,             focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,             focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,             tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,             tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,   setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,  setborderpx,    {.i = +1 } },
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
    // removing 6-9 tags not being used EVER - fix this eventually if need be
	// TAGKEYS(                        XK_7,                               6)
	// TAGKEYS(                        XK_8,                               7)
	// TAGKEYS(                        XK_9,                               8)
    { MODKEY|ControlMask|ShiftMask, XK_q,              quit,           {0} }, 
	{ MODKEY|ShiftMask,             XK_q,              quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                          event mask      button          function        argument */
	{ ClkLtSymbol,                    0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,                    0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,                    0,              Button2,        zoom,           {0} },
	{ ClkStatusText,                  0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,                  0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,                  0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,                  0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,                  0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,                  ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,                   MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,                   MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,                   MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,                      0,              Button1,        view,           {0} },
	{ ClkTagBar,                      0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,                      MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,                      MODKEY,         Button3,        toggletag,      {0} },
};
