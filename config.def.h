/* See LICENSE file for copyright and license details. */
/*
 *     _   __  _                __
 *    / | / / (_)___  _________/ /
 *   /  |/ / / / __ \/ ___/ __  / 
 *  / /|  / / / /_/ / /  / /_/ /  
 * /_/ |_/_/ /\____/_/   \__,_/   
 *      /___/                     
*/

/* Auxiliary libraries */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_darkred[]     = "#990000";
static const char col_orange[]      = "#d08770";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
        [SchemeSel]  = { col_gray4, col_darkred,  col_cyan  },
};

/* tagging unicode(requires Nerd Fonts) */
static const char *tags[] = { "\uf306", "\uf484", "\uf670", "\uf7b3", "\ue22b",
    "\ufd1d", "\uf001", "\uf7cd", "\uf6c3" };
static const char *tagsalt[] = { "\uf8a3", "\uf8a6", "\uf8a9", "\uf8ac", "\uf8af", "\uf8b2", 
    "\uf8b5", "\uf8b8", "\uf8bb" };
/* Default tags */
/*static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            0,           -1 },
};

/* if it's needed to autostart a program, add a system entry here
 * in the background, otherwise it causes the window manager to bug */
const char *startuphook[] = {
         "dunst &"     ,
         "compton -b"  ,
         "~/.fehbg"    ,
         "slstatus &"  ,
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\ufb3f",   tile },    /* first entry is default */
	{ "\uf53d",   NULL },    /* no layout function means floating behavior */
	{ "\ufad7",   monocle },
        { "\ufa6f",   grid},
	{ "\ufa6a",   centeredmaster },
	{ "\ufa6b",   centeredfloatingmaster },
 	{ "\ufa73",   spiral },
 	{ "\ufd41",   dwindle },
	{ NULL,       NULL },   /* necessary to be able to loop over */
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

/* Application Defaults */
static const char menurunner[6]         = "dmenu"; /* interactive menu application */
static const char browsername[10]       = "firefox"; /* browser to be user on definitions */
static const char filebrowsername[7]    = "ranger"; /* console file browser */
static const char musicplayername[8]    = "ncmpcpp"; /* music player management */
static const char calendarname[9]       = "calcurse"; /* calendar application */
static const char calculatorname[5]     = "ghci"; /* calculator application */
static const char irccname[6]           = "irssi"; /* social irc client application */

/* commands */
/* General commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_darkred, "-sf", col_gray4, NULL };
static const char termname[]    = "st"; /* terminal name to be used on definitions */
static const char *termcmd[]    = { "st" , NULL };
static const char *lockcmd[]    = { "slock", NULL };
/* Multimedia commands */
/* Audio commands */
static const char *volup[]      = { "pactl", "set-sink-volume", "0", "+5%", NULL }; 
static const char *voldown[]    = { "pactl", "set-sink-volume", "0", "-5%", NULL }; 
static const char *volmute[]    = { "pactl", "set-sink-mute", "0", "toggle", NULL }; 
/* Media Player commands */
static const char *mediatoggle[]    = { "mpc", "toggle", NULL };
static const char *mediastop[]      = { "mpc", "stop", NULL };
static const char *mediaprev[]      = { "mpc", "prev", NULL };
static const char *medianext[]      = { "mpc", "next", NULL };
/* Screen Brightness commands */
static const char *brightup[]     = { "brightnessctl" , "set", "+10%", NULL};
static const char *brightdown[]   = { "brightnessctl" , "set", "10%-", NULL};

/* Application specific commands */
static const char *browser[]        = { browsername, NULL };
static const char *filebrowser[]    = { termname, "-e", filebrowsername, NULL };
static const char *musicplayer[]    = { termname, "-e", musicplayername, NULL };
static const char *calendar[]       = { termname, "-e", calendarname, NULL };
static const char *calculator[]     = { termname, "-e", calculatorname, NULL };
static const char *socialclient[]   = { termname, "-e", irccname, NULL };

static Key keys[] = {
	/* modifier                     key            function        argument */
	{ MODKEY,                       XK_d,          spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,     zoom,           {0} },
	{ MODKEY,                       XK_Tab,        view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,     {0} },
	{ MODKEY,                       XK_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,          setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_c,          setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_s,          setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,		XK_semicolon,  cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,          togglealttag,   {0} },
	TAGKEYS(                        XK_1,                          0)
	TAGKEYS(                        XK_2,                          1)
	TAGKEYS(                        XK_3,                          2)
	TAGKEYS(                        XK_4,                          3)
	TAGKEYS(                        XK_5,                          4)
	TAGKEYS(                        XK_6,                          5)
	TAGKEYS(                        XK_7,                          6)
	TAGKEYS(                        XK_8,                          7)
	TAGKEYS(                        XK_9,                          8)
	{ MODKEY|ShiftMask,             XK_q,          quit,           {0} },
	{ MODKEY|ControlMask,             XK_l,          spawn,          {.v = lockcmd } },
        { 0,                            XK_Print,      printscreen,    {0} },
        /* Multimedia Keys */
        /* Audio keys */
        { 0,                        XF86XK_AudioRaiseVolume, spawn, {.v = volup } },
        { 0,                        XF86XK_AudioLowerVolume, spawn, {.v = voldown } },
        { 0,                        XF86XK_AudioMute, spawn, {.v = volmute } },
        /* Media Player keys */
        { 0,                        XF86XK_AudioPlay, spawn, {.v = mediatoggle } },
        { ShiftMask,                XF86XK_AudioPlay, spawn, {.v = mediastop } },
        { 0,                        XF86XK_AudioPrev, spawn, {.v = mediaprev } },
        { 0,                        XF86XK_AudioNext, spawn, {.v = medianext } },
        /* Brightness keys */
        { 0,                        XF86XK_MonBrightnessUp, spawn, {.v = brightup } },
        { 0,                        XF86XK_MonBrightnessDown, spawn, {.v = brightdown } },

        /* Application keys */
        { MODKEY|ControlMask,           XK_b,         spawn,    {.v = browser } },
        { MODKEY|ControlMask,           XK_f,         spawn,    {.v = filebrowser } },
        { MODKEY|ControlMask,           XK_m,         spawn,    {.v = musicplayer } },
        { MODKEY|ControlMask,           XK_p,         spawn,    {.v = calendar } },
        { MODKEY|ControlMask,           XK_c,         spawn,    {.v = calculator } },
        { MODKEY|ControlMask,           XK_s,         spawn,    {.v = socialclient} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

