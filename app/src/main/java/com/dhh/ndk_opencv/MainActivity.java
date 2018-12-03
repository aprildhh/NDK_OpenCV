package com.dhh.ndk_opencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private ImageView sampleText;
    private Bitmap bitmap;


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary ( "native-lib" );
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_main );

        // Example of a call to a native method
        sampleText = (ImageView) findViewById ( R.id.sample_text );
        bitmap = BitmapFactory.decodeResource ( getResources (), R.mipmap.timg );

        stringFromJNI ();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public static native int[] grayP(int[] pixels, int w, int h);

    public void changeColor(View view) {
        int w = bitmap.getWidth ();
        int h = bitmap.getHeight ();
        int[] pixels = new int[w * h];
        bitmap.getPixels ( pixels, 0, w, 0, 0, w, h );
        int[] resultInt = grayP ( pixels, w, h );
        Bitmap resultImg = Bitmap.createBitmap ( w,h,Bitmap.Config.ARGB_8888 );
        resultImg.setPixels ( resultInt,0,w,0,0,w,h );
        sampleText.setImageBitmap ( resultImg );
    }
}
