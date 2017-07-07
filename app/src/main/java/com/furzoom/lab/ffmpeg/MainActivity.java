package com.furzoom.lab.ffmpeg;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "MainActivity";
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnConfigure = (Button) findViewById(R.id.btn_configure);
        Button btnProtocol = (Button) findViewById(R.id.btn_protocol);
        Button btnFormat = (Button) findViewById(R.id.btn_format);
        Button btnCodec = (Button) findViewById(R.id.btn_codec);
        Button btnFilter = (Button) findViewById(R.id.btn_filter);

        btnConfigure.setOnClickListener(this);
        btnProtocol.setOnClickListener(this);
        btnFormat.setOnClickListener(this);
        btnCodec.setOnClickListener(this);
        btnFilter.setOnClickListener(this);

        tv = (TextView) findViewById(R.id.sample_text);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String configure();
    public native String urlprotocolinfo();
    public native String avformatinfo();
    public native String avcodecinfo();
    public native String avfilterinfo();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_configure:
                tv.setText(configure());
                break;
            case R.id.btn_protocol:
                tv.setText(urlprotocolinfo());
                break;
            case R.id.btn_format:
                tv.setText(avformatinfo());
                break;
            case R.id.btn_codec:
                tv.setText(avcodecinfo());
                break;
            case R.id.btn_filter:
                Log.d(TAG, "onClick: btn_filter");
                tv.setText(avfilterinfo());
                Log.d(TAG, "After: btn_filter");
                break;
            default:
                break;
        }
    }
}
