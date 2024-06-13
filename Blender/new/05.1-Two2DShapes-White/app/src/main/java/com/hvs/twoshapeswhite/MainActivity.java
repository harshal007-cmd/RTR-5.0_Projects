package com.hvs.twoshapeswhite;

import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.WindowCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.core.view.WindowInsetsControllerCompat;

public class MainActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {

        super.onCreate(savedInstanceState);

        //Fullscreen
        //Get and hide action bar
        getSupportActionBar().hide();

        //Do full screen
        WindowCompat.setDecorFitsSystemWindows(getWindow(),false);

        //Get window inset controller object
        WindowInsetsControllerCompat windowInsetsControllerCompat = WindowCompat.getInsetsController(getWindow(), getWindow().getDecorView());

        //Tell above object to hide system bars, means status, navigation, caption and IME-Input method editor
        windowInsetsControllerCompat.hide(WindowInsetsCompat.Type.systemBars() | WindowInsetsCompat.Type.ime());

        //Do Landscape
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        //setting background color to black
        getWindow().getDecorView().setBackgroundColor(Color.BLACK);

        GLESView glesView = new GLESView(this);

        setContentView(glesView);
        
    }

    @Override
    protected void onPause()
    {
        super.onPause();
    }

    @Override
    protected void onResume(){
        super.onResume();
    }
}