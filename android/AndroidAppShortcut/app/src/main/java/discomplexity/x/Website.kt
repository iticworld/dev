package discomplexity.x

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.net.Uri
import java.io.BufferedInputStream
import java.net.URL
import java.net.URLConnection

class Website {

    companion object {
        fun favicon(uri: Uri): Bitmap? {
            val icon: Uri = uri.buildUpon().path("favicon.ico").build()
            return try {
                val connection: URLConnection = URL(icon.toString()).openConnection()
                connection.connect()
                BitmapFactory.decodeStream(BufferedInputStream(connection.getInputStream(), 8192))
            } catch(e: Exception) {
                null
            }
        }

        fun host(uri: Uri): String {
            if(uri.host != null){
                return uri.host!!
            }
            return ""
        }

        fun full(uri: Uri): String {
            return uri.toString()
        }
    }
}