package com.google.engedu.puzzle8;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import java.util.ArrayList;
import java.util.List;


public class PuzzleActivity extends AppCompatActivity {


    private ImageView ivphoto;
    private Button photo_button, shuffle_button, solve_button;
    static final int REQUEST_IMAGE_CAPTURE = 1;
    private Bitmap imageBitmap = null;
    private PuzzleBoardView boardView;
    RelativeLayout container;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_puzzle);


        ivphoto = (ImageView)findViewById(R.id.ivPhoto);
        photo_button = (Button)findViewById(R.id.photo_button);
        solve_button = (Button)findViewById(R.id.solve_button);
        shuffle_button = (Button)findViewById(R.id.shuffle_button);


        // This code programmatically adds the PuzzleBoardView to the UI.
        container = (RelativeLayout) findViewById(R.id.puzzle_container);
        boardView = new PuzzleBoardView(this);
        // Some setup of the view.
        boardView.setLayoutParams(new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT));
        container.addView(boardView);


        if(haveReadWritePermissions(PuzzleActivity.this)==false) {
            requestPermission(PuzzleActivity.this);
            return;
        }
    }

    public void dispatchTakePictureIntent(View view) {


        if(haveReadWritePermissions(PuzzleActivity.this)==false) {
            requestPermission(PuzzleActivity.this);
            return;
        }
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if(takePictureIntent.resolveActivity(getPackageManager())!=null)
        {
            startActivityForResult(takePictureIntent,REQUEST_IMAGE_CAPTURE);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if(requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK)
        {
            Bundle extras = data.getExtras();
            imageBitmap = (Bitmap)extras.get("data");
             boardView.initialize(imageBitmap,container);
            //ivphoto.setImageBitmap(imageBitmap);
        }

    }

    public void shuffleImage(View view) {

        if(haveReadWritePermissions(PuzzleActivity.this)==false) {
            requestPermission(PuzzleActivity.this);
            return;
        }
        boardView.shuffle();
    }

    public void solve(View view) {

        if(haveReadWritePermissions(PuzzleActivity.this)==false) {
            requestPermission(PuzzleActivity.this);
            return;
        }
        boardView.solve();
    }

    public static boolean haveReadWritePermissions(Activity caller) {
        int permissionCheck = ContextCompat.checkSelfPermission(caller,
                Manifest.permission.CAMERA);

        if (permissionCheck== PackageManager.PERMISSION_GRANTED)
        {
            permissionCheck = ContextCompat.checkSelfPermission(caller,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE);

            if (permissionCheck== PackageManager.PERMISSION_GRANTED)
                return true;
        }

        return false;
    }

    public static void requestPermission(Activity caller) {
        List<String> permissionList = new ArrayList<String>();

        if  (ContextCompat.checkSelfPermission(caller, Manifest.permission.CAMERA)!=PackageManager.PERMISSION_GRANTED)
            permissionList.add(Manifest.permission.CAMERA);

        if  (ContextCompat.checkSelfPermission(caller, Manifest.permission.WRITE_EXTERNAL_STORAGE)!=PackageManager.PERMISSION_GRANTED)
            permissionList.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);

        if (permissionList.size()>0)
        {
            String [] permissionArray = new String[permissionList.size()];

            for (int i=0;i<permissionList.size();i++)
                permissionArray[i] = permissionList.get(i);

            ActivityCompat.requestPermissions(caller, permissionArray,99);
        }
    }

}
