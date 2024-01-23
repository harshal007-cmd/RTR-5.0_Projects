#include<stdio.h>
#include<stdlib.h>


#define WIN_WIDTH 640
#define WIN_HEIGHT 360

#define MAP_X	32				// size of map along x-axis
#define MAP_Z	32				// size of map along z-axis
#define MAP_SCALE	20.0f		// the scale of the terrain map

GLfloat eyeX, eyeY, eyeZ, lookX, lookY, lookZ;
GLfloat mouseX, mouseY;

PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2f = NULL;
PFNGLACTIVETEXTUREPROC   glActiveTexture = NULL;

// Terrain Varriables
GLfloat angle = 0.0f;				// camera angle 
GLfloat radians = 0.0f;			// camera angle in radians
GLfloat waterHeight = 154.0f;		// height of water
BOOL waterDir = true;			// used to animate water; true = up, false = down

GLuint texture_land;
GLuint texture_water;
unsigned char* heightmapData;

GLfloat terrain[MAP_X][MAP_Z][3];

void InitTerrain()
{
    for (int z = 0; z < MAP_Z; z++)
    {
        for (int x = 0; x < MAP_X; x++)
        {
            terrain[x][z][0] = float(x) * MAP_SCALE;
            terrain[x][z][1] = (float)heightmapData[(z * MAP_Z + x) * 3];
            terrain[x][z][2] = -float(z) * MAP_SCALE;
        }
    }
}


GLuint createTexture2D(const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channel;
    unsigned char* data = stbi_load(filePath, &width, &height, &channel, 0);

    if (!data)
    {
      //  fprintf(gpFILE, "Failed To Load %s Texture\n", filePath);
        return -1;
    }

    GLenum format = GL_RGBA;

    if (channel == STBI_grey)
        format = GL_RED;
    else if (channel == STBI_rgb)
        format = GL_RGB;
    else if (channel == STBI_rgb_alpha)
        format = GL_RGBA;

    GLuint texture;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return texture;
}

BOOL LoadGLTexture(GLuint* texture, TCHAR img_src[])
{
    HBITMAP hBitmap = NULL;
    BITMAP bmp;
    BOOL bResult = FALSE;
    hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), img_src, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hBitmap)
    {
        bResult = TRUE;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        //Create Texture
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
        glBindTexture(GL_TEXTURE_2D, 0);
        DeleteObject(hBitmap);
    }
    return bResult;
}


void displayTerrain()
{
    GLfloat radians = M_PI * (angle - 90.0f) / 180.0f;

    eyeX = lookX + sin(radians) * mouseY;
    eyeZ = lookZ + cos(radians) * mouseY;
    eyeY = lookY + mouseY / 2.0f;

    lookX = (MAP_X * MAP_SCALE) / 2.0f;
    lookY = 150.0f;
    lookZ = -(MAP_Z * MAP_SCALE) / 2.0f;

    // Code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture_land);
    for (int z = 0; z < MAP_Z - 1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < MAP_X - 1; x++)
        {
            glTexCoord2f(0.0f, 0.0f);
            glColor3f(terrain[x][z][1] / 255.0f, terrain[x][z][1] / 255.0f, terrain[x][z][1] / 255.0f);
            glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

            glTexCoord2f(1.0f, 0.0f);
            glColor3f(terrain[x + 1][z][1] / 255.0f, terrain[x + 1][z][1] / 255.0f, terrain[x + 1][z][1] / 255.0f);
            glVertex3f(terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);

            glTexCoord2f(0.0f, 1.0f);
            glColor3f(terrain[x][z + 1][1] / 255.0f, terrain[x][z + 1][1] / 255.0f, terrain[x][z + 1][1] / 255.0f);
            glVertex3f(terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            glTexCoord2f(1.0f, 1.0f);
            glColor3f(terrain[x + 1][z + 1][1] / 255.0f, terrain[x + 1][z + 1][1] / 255.0f, terrain[x + 1][z + 1][1] / 255.0f);
            glVertex3f(terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1], terrain[x + 1][z + 1][2]);
        }
        glEnd();
    }

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.5f, 0.5f, 1.0f, 0.7f);
    glBindTexture(GL_TEXTURE_2D, texture_water);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(terrain[0][0][0], waterHeight, terrain[0][0][2]);

    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(terrain[MAP_X - 1][0][0], waterHeight, terrain[MAP_X - 1][0][2]);

    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(terrain[MAP_X - 1][MAP_Z - 1][0], waterHeight, terrain[MAP_X - 1][MAP_Z - 1][2]);

    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(terrain[0][MAP_Z - 1][0], waterHeight, terrain[0][MAP_Z - 1][2]);
    glEnd();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  
}