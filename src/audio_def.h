#define XA_LENGTH(x) (((u64)(x) * 75) / 100 * IO_SECT_SIZE) //Centiseconds to sectors in bytes (w)
#define XA_MINUTES(x)(((u64)(x) / 75) / IO_SECT_SIZE) - 1; //Convert XA_LENGTH in seconds - 1

typedef struct
{
	XA_File file;
	u32 length;
} XA_TrackDef;

static const XA_TrackDef xa_tracks[] = {
	//MENU.XA
	{XA_Menu, XA_LENGTH(11300)}, //XA_GettinFreaky
	{XA_Menu, XA_LENGTH(400)},  //XA_MicDrop
	{XA_Menu, XA_LENGTH(3800)},  //XA_GameOver
	//WEEK1A.XA
	{XA_Week1A, XA_LENGTH(7800)}, //XA_Bopeebo
	{XA_Week1A, XA_LENGTH(8000)}, //XA_Fresh
	//WEEK1B.XA
	{XA_Week1B, XA_LENGTH(8700)}, //XA_Dadbattle
	{XA_Week1B, XA_LENGTH(6800)}, //XA_Tutorial
};

static const char *xa_paths[] = {
	"\\MUSIC\\MENU.XA;1",   //XA_Menu
	"\\MUSIC\\WEEK1A.XA;1", //XA_Week1A
	"\\MUSIC\\WEEK1B.XA;1", //XA_Week1B
	NULL,
};
