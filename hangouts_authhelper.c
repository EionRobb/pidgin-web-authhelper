#define PURPLE_PLUGINS

#define HANGOUTS_AUTH_URL ""

#include <purple.h>
#include "webview.h"

static struct webview *webview = NULL;
guint webview_loop = 0;

gboolean
authhelper_webview_loop(gpointer userdata)
{
	struct webview *thewebview = userdata;
	return webview_loop(thewebview, 0) ? TRUE : FALSE;
}

static void
authhelper_openbrowser()
{
	webview = g_new0(struct webview, 1);
	webview->title = "Hangouts Authenticaion";
	webview->url = HANGOUTS_AUTH_URL;
	webview->width = 400;
	webview->height = 600;
	
	webview_init(webview);
	g_idle_add(authhelper_webview_loop, webview);
}

static gboolean
plugin_load(PurplePlugin *plugin, GError **error)
{
	// listen to purple_notify_uri signals
	//check for https://www.youtube.com/watch?v=hlDhp-eNLMU url
}

static gboolean
plugin_unload(PurplePlugin *plugin, GError **error)
{
	purple_signals_disconnect_by_handle(plugin);
	
	return TRUE;
}


#if !PURPLE_VERSION_CHECK(3, 0, 0)

static gboolean
libpurple2_plugin_load(PurplePlugin *plugin)
{
	return plugin_load(plugin, NULL);
}

static gboolean
libpurple2_plugin_unload(PurplePlugin *plugin)
{
	return plugin_unload(plugin, NULL);
}

static PurplePluginInfo info =
{
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_PROTOCOL,                             /**< type           */
	NULL,                                               /**< ui_requirement */
	0,                                                  /**< flags          */
	NULL,                                               /**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,                            /**< priority       */

	"hangouts-authhelper",                                 /**< id             */
	N_("Hangouts Auth Helper"),                                     /**< name           */
	HANGOUTS_PLUGIN_VERSION,                            /**< version        */
	                                 
	N_("Hangouts Authentication Helper."),                   /**< summary        */
	                                                  
	N_("Makes it easier to auth with Hangouts by creating a web browser."), /**< description    */
	"Eion Robb <eionrobb+hangouts@gmail.com>",          /**< author         */
	"https://bitbucket.org/EionRobb/purple-hangouts/",  /**< homepage       */

	libpurple2_plugin_load,                             /**< load           */
	libpurple2_plugin_unload,                           /**< unload         */
	NULL,                                               /**< destroy        */

	NULL,                                               /**< ui_info        */
	NULL,                                               /**< extra_info     */
	NULL,                                               /**< prefs_info     */
	NULL,                                               /**< actions        */

	/* padding */
	NULL,
	NULL,
	NULL,
	NULL
};

static void
init_plugin(PurplePlugin *plugin)
{
	// add dependency for hangouts prpl
}

PURPLE_INIT_PLUGIN(hangouts_authhelper, init_plugin, info);

#endif