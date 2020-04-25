package discomplexity.x.app

import android.content.Context
import android.content.Intent
import android.content.pm.ShortcutInfo
import android.content.pm.ShortcutManager
import android.graphics.drawable.Icon
import android.net.Uri
import android.os.Build
import android.os.PersistableBundle
import discomplexity.x.Website
import discomplexity.x.app.shortcut.R
import java.lang.RuntimeException


class Shortcut {

    private var __context: Context? = null
    private var __manager: ShortcutManager? = null

    constructor(context: Context) {
        __context = context
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N_MR1) {
            __manager = __context!!.getSystemService(Context.SHORTCUT_SERVICE) as ShortcutManager?
        }
    }

    companion object {
        const val EXTRA_LAST_REFRESH: String = "discomplexity.x.app.shortcut.EXTRA_LAST_REFRESH"
    }

    fun maybeRestoreAllDynamicShortcuts(): Boolean {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N_MR1) {
            return __manager!!.dynamicShortcuts.size == 0
        } else {
            throw RuntimeException()
        }
    }

    fun report(id: String?) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N_MR1) {
            __manager!!.reportShortcutUsed(id)
        } else {
            throw RuntimeException()
        }
    }

    fun get(): List<ShortcutInfo> {
        val result: MutableList<ShortcutInfo> = ArrayList()
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N_MR1) {
            val keys: HashSet<String> = HashSet()
            for(shortcut in __manager!!.dynamicShortcuts) {
                if(!shortcut.isImmutable) {
                    result.add(shortcut)
                    keys.add(shortcut.id)
                }
            }
            for(shortcut in __manager!!.pinnedShortcuts) {
                if(!shortcut.isImmutable && !keys.contains(shortcut.id)) {
                    result.add(shortcut)
                    keys.add(shortcut.id)
                }
            }
        }
        return result
    }

    fun create(url: String): ShortcutInfo {
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.N_MR1) {
            val builder = ShortcutInfo.Builder(__context, url)
            val uri: Uri = Uri.parse(url)
            builder.setIntent(Intent(Intent.ACTION_VIEW, uri))
            if(uri.host != null) {
                builder.setShortLabel(uri.host!!)
            } else {
                builder.setShortLabel("uri")
            }
            builder.setShortLabel(Website.host(uri))
            builder.setLongLabel(Website.full(uri))
            val bmp = Website.favicon(uri)
            if(bmp != null){
                builder.setIcon(Icon.createWithBitmap(bmp))
            } else {
                builder.setIcon(Icon.createWithResource(__context, R.drawable.link))
            }

            val extras = PersistableBundle()
            extras.putLong(EXTRA_LAST_REFRESH, System.currentTimeMillis())
            builder.setExtras(extras)

            return builder.build()
        } else {
            throw RuntimeException()
        }
    }

//    private fun createShortcutForUrl(urlAsString: String): ShortcutInfo {
//        Log.i(TAG, "createShortcutForUrl: $urlAsString")
//        val b = ShortcutInfo.Builder(mContext, urlAsString)
//        val uri: Uri = Uri.parse(urlAsString)
//        b.setIntent(Intent(Intent.ACTION_VIEW, uri))
//        setSiteInformation(b, uri)
//        setExtras(b)
//        return b.build()
//    }


//    private val TAG: String = Main.TAG
//
//    private val EXTRA_LAST_REFRESH =
//        "com.example.android.shortcutsample.EXTRA_LAST_REFRESH"
//
//    private val REFRESH_INTERVAL_MS = 60 * 60 * 1000.toLong()

//
//    /**
//     * Use this when interacting with ShortcutManager to show consistent error messages.
//     */
//    private fun callShortcutManager(r: BooleanSupplier) {
//        try {
//            if (!r.getAsBoolean()) {
//                Utils.showToast(mContext, "Call to ShortcutManager is rate-limited")
//            }
//        } catch (e: Exception) {
//            Log.e(TAG, "Caught Exception", e)
//            Utils.showToast(mContext, "Error while calling ShortcutManager: $e")
//        }
//    }
//
//    /**
//     * Return all mutable shortcuts from this app self.
//     */

//
//    /**
//     * Called when the activity starts.  Looks for shortcuts that have been pushed and refreshes
//     * them (but the refresh part isn't implemented yet...).
//     */
//    fun refreshShortcuts(force: Boolean) {
//        object : AsyncTask<Void?, Void?, Void?>() {
//            protected fun doInBackground(vararg params: Void): Void? {
//                Log.i(TAG, "refreshingShortcuts...")
//                val now = System.currentTimeMillis()
//                val staleThreshold = if (force) now else now - REFRESH_INTERVAL_MS
//
//                // Check all existing dynamic and pinned shortcut, and if their last refresh
//                // time is older than a certain threshold, update them.
//                val updateList: MutableList<ShortcutInfo> = ArrayList()
//                for (shortcut in getShortcuts()) {
//                    if (shortcut.isImmutable) {
//                        continue
//                    }
//                    val extras = shortcut.extras
//                    if (extras != null && extras.getLong(EXTRA_LAST_REFRESH) >= staleThreshold) {
//                        // Shortcut still fresh.
//                        continue
//                    }
//                    Log.i(TAG, "Refreshing shortcut: " + shortcut.id)
//                    val b = ShortcutInfo.Builder(
//                        mContext, shortcut.id
//                    )
//                    setSiteInformation(b, shortcut.intent!!.data)
//                    setExtras(b)
//                    updateList.add(b.build())
//                }
//                // Call update.
//                if (updateList.size > 0) {
//                    callShortcutManager(BooleanSupplier {
//                        mShortcutManager!!.updateShortcuts(
//                            updateList
//                        )
//                    })
//                }
//                return null
//            }
//        }.execute()
//    }
//
//    private fun createShortcutForUrl(urlAsString: String): ShortcutInfo {
//        Log.i(TAG, "createShortcutForUrl: $urlAsString")
//        val b = ShortcutInfo.Builder(mContext, urlAsString)
//        val uri: Uri = Uri.parse(urlAsString)
//        b.setIntent(Intent(Intent.ACTION_VIEW, uri))
//        setSiteInformation(b, uri)
//        setExtras(b)
//        return b.build()
//    }
//
//    private fun setSiteInformation(b: ShortcutInfo.Builder, uri: Uri?): ShortcutInfo.Builder? {
//        // TODO Get the actual site <title> and use it.
//        // TODO Set the current locale to accept-language to get localized title.
//        b.setShortLabel(uri.getHost())
//        b.setLongLabel(uri.toString())
//        val bmp = fetchFavicon(uri)
//        if (bmp != null) {
//            b.setIcon(Icon.createWithBitmap(bmp))
//        } else {
//            b.setIcon(Icon.createWithResource(mContext, R.drawable.link))
//        }
//        return b
//    }
//
//    private fun setExtras(b: ShortcutInfo.Builder): ShortcutInfo.Builder? {
//        val extras = PersistableBundle()
//        extras.putLong(EXTRA_LAST_REFRESH, System.currentTimeMillis())
//        b.setExtras(extras)
//        return b
//    }
//
//    private fun normalizeUrl(urlAsString: String): String {
//        return if (urlAsString.startsWith("http://") || urlAsString.startsWith("https://")) {
//            urlAsString
//        } else {
//            "http://$urlAsString"
//        }
//    }
//
//    fun addWebSiteShortcut(urlAsString: String) {
//        callShortcutManager(BooleanSupplier {
//            val shortcut = createShortcutForUrl(normalizeUrl(urlAsString))
//            mShortcutManager!!.addDynamicShortcuts(Arrays.asList(shortcut))
//        })
//    }
//
//    fun removeShortcut(shortcut: ShortcutInfo) {
//        mShortcutManager!!.removeDynamicShortcuts(Arrays.asList(shortcut.id))
//    }
//
//    fun disableShortcut(shortcut: ShortcutInfo) {
//        mShortcutManager!!.disableShortcuts(Arrays.asList(shortcut.id))
//    }
//
//    fun enableShortcut(shortcut: ShortcutInfo) {
//        mShortcutManager!!.enableShortcuts(Arrays.asList(shortcut.id))
//    }
//
}