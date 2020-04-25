package discomplexity.x.app.shortcut

import android.app.ListActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.inputmethod.EditorInfo

import android.widget.EditText
import discomplexity.x.app.Shortcut


class MainActivity: ListActivity(), View.OnClickListener {

    private var __shortcut: Shortcut? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.app_shortcut_main)

        __shortcut = Shortcut(this)
        __shortcut!!.get().forEach{info -> Log.e("TAG", info.id)}
    }

    override fun onClick(v: View?) {
        TODO("Not yet implemented")
    }

    fun onAddPressed(v: View?) {
        addWebSite()
        Log.e("TAG", "ON ADD PRESSED")
    }

    private fun addWebSite() {
//        mHelper.reportShortcutUsed(ID_ADD_WEBSITE)
//
//        val editUri = EditText(this)
//
//        editUri.hint = "http://www.android.com/"
//        editUri.inputType = EditorInfo.TYPE_TEXT_VARIATION_URI
//
//        Builder(this)
//            .setTitle("Add new website")
//            .setMessage("Type URL of a website")
//            .setView(editUri)
//            .setPositiveButton("Add", { dialog, whichButton ->
//                val url = editUri.text.toString().trim { it <= ' ' }
//                if (url.length > 0) {
//                    addUriAsync(url)
//                }
//            })
//            .show()
    }

}
