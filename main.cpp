#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#define SPEED 30.0
#include <time.h>
#include <math.h>
#define RAINSIZE 500
//for car
float i=0.0;
float j=0.0;
//for cloud
float m=0.0;
//for airplane x axis
float n=0.0;
//y axis
float o=0.0;
//for star x axis
float p=0.0;
//y axis
float q=0.0;
//sun y axis
float a=0.0;
//moon y axis
float b=0.0;
int light=1;
int day=1;
int raining=1;
int plane=0;
int fallen_star=0;
int winWidth = 1200, winHeight = 700;
float rotationAngle = 0;

void draw_pixel(GLint cx, GLint cy)
{
	glBegin(GL_POINTS);
    glVertex2i(cx,cy);
	glEnd();
}

void plotpixels(GLint h,GLint k, GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}

struct drop
{
    float x = 400;
    float y = 400;
    float inc = 0.01;
    float radius = 5;
    float scale = 1.0;
    float rotationAngle = 0;
    float rotationInc = 1;
};
drop rain[RAINSIZE];

void Rain()
{
    for (int i = 0; i < RAINSIZE; i++) {
        rain[i].x = rand() % winWidth;
        rain[i].y = rand() % winHeight;
        rain[i].inc = 1.5 + (float)(rand() % 100) / 1000.0;
        rain[i].radius = (float)(rand() % 8);
        rain[i].scale = (float)(rand() % 20000) / 1000.0;
        rain[i].rotationAngle = (float)(rand() % 3000) / 1000.0;
        rain[i].rotationInc = (float)(rand() % 100) / 1000.0;
        if ((rand() % 100) > 50)
            {
            rain[i].rotationInc = -rain[i].rotationInc;
            }
        }

}

void drawParticleShape(int i)
{
    glBegin(GL_POINTS);
    glVertex2f(rain[i].x, rain[i].y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(rain[i].x, rain[i].y);
    glVertex2f(rain[i].x, rain[i].y + rain[i].radius * 2);
    glEnd();
}

void drawDrop(int i)
{
    glColor3f(0.6, 0.7, 0.8);
    glLineWidth(1);
    drawParticleShape(i);
    rain[i].y -= rain[i].inc;
    if (rain[i].y < 0)
    {
        rain[i].y = winHeight;
    }
}

void drawRain()
{
    if(raining==0)
    {
        Rain();
        for (int i = 0; i < RAINSIZE; i++)
            {
                drawDrop(i);
            }
    }

    else
    {

    }

}

void draw_circle(GLint h, GLint k, GLint r)
{
	GLint d=1-r, x=0, y=r;
	while(y>x)
	{
		plotpixels(h,k,x,y);
		if(d<0) d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}

void sun()
{
    int l;
    for(l=0;l<=50;l++)
        {
            glColor3f(1.0, 0.6, 0.0);
            draw_circle(1000,755+a,l);
        }

}

void moon()
{
    int l;
        for(l=0;l<=35;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(100,745+b,l);
        }
    float x,y;
    int i;
    GLfloat r;
    int triangleAmount=40;
    GLfloat twicePi = 2.0*3.1416;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    x= 115,y=755+b,r=35;

    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++){
    glVertex2f(
        x+(r*cos(i*twicePi/triangleAmount)),
        y+(r*sin(i*twicePi/triangleAmount))
        );
    }
    glEnd();
}

void draw_object()
{
    int l;
    if(day==1)
    {
        if(raining==1)
        {

            glColor3f(0.0,0.9,0.9);                      //sky
            glBegin(GL_POLYGON);
            glVertex2f(0,350);
            glVertex2f(0,700);
            glVertex2f(1200,700);
            glVertex2f(1200,350);
            glEnd();

            sun();

            for(l=0;l<=50;l++)                          //cloud2
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(40+m,615,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(60+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(100+m,625,l);
                draw_circle(115+m,625,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(145+m,625,l);
            }

            for(l=0;l<=20;l++)                          //cloud2
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(370+m,600,l);
            }
            for(l=0;l<=35;l++)
            {

                glColor3f(1.0,1.0,1.0);
                draw_circle(410+m,605,l);
                draw_circle(435+m,595,l);
                draw_circle(470+m,605,l);
            }

            for(l=0;l<=20;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(500+m,615,l);
            }

            for(l=0;l<=30;l++)                //cloud3
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(700+m,615,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(700+m,635,l);
                draw_circle(725+m,625,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(765+m,645,l);
            }

            for(l=0;l<=50;l++)                          //cloud4
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(920+m,625,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(960+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1000+m,625,l);
                draw_circle(1015+m,625,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1045+m,625,l);
            }
            for(l=0;l<=50;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(940+m,615,l);
            }

            for(l=0;l<=20;l++)                           //cloud5
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1270+m,600,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1210+m,605,l);
                draw_circle(1235+m,595,l);
                draw_circle(1270+m,605,l);
            }

            for(l=0;l<=20;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1300+m,615,l);
            }
            for(l=0;l<=40;l++)                           //cloud6
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1570+m,600,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1510+m,605,l);
                draw_circle(1535+m,595,l);
                draw_circle(1570+m,605,l);
            }

            for(l=0;l<=40;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1600+m,615,l);
            }


            for(l=0;l<=30;l++)                              //cloud7
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1770+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1700+m,625,l);
                draw_circle(1750+m,610,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(1.0,1.0,1.0);
                draw_circle(1745+m,625,l);
            }
                                            //grass
        glColor3f(0.0,0.9,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,160);
        glVertex2f(0,450);
        glVertex2f(1200,450);
        glVertex2f(1200,160);
        glEnd();

}
        else
        {
            glColor3f(0.0,0.7,0.7);                      //sky
            glBegin(GL_POLYGON);
            glVertex2f(0,350);
            glVertex2f(0,700);
            glVertex2f(1200,700);
            glVertex2f(1200,350);
            glEnd();

            for(l=0;l<=50;l++)                          //cloud2
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(40+m,615,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(60+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(100+m,625,l);
                draw_circle(115+m,625,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(145+m,625,l);
            }

            for(l=0;l<=20;l++)                          //cloud2
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(370+m,600,l);
            }
            for(l=0;l<=35;l++)
            {

                glColor3f(0.9,0.9,0.9);
                draw_circle(410+m,605,l);
                draw_circle(435+m,595,l);
                draw_circle(470+m,605,l);
            }

            for(l=0;l<=20;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(500+m,615,l);
            }

            for(l=0;l<=30;l++)                //cloud3
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(700+m,615,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(700+m,635,l);
                draw_circle(725+m,625,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(765+m,645,l);
            }

            for(l=0;l<=50;l++)                          //cloud4
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(920+m,625,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(960+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1000+m,625,l);
                draw_circle(1015+m,625,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1045+m,625,l);
            }
            for(l=0;l<=50;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(940+m,615,l);
            }

            for(l=0;l<=20;l++)                           //cloud5
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1270+m,600,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1210+m,605,l);
                draw_circle(1235+m,595,l);
                draw_circle(1270+m,605,l);
            }

            for(l=0;l<=20;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1300+m,615,l);
            }
            for(l=0;l<=40;l++)                           //cloud6
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1570+m,600,l);
            }
            for(l=0;l<=30;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1510+m,605,l);
                draw_circle(1535+m,595,l);
                draw_circle(1570+m,605,l);
            }

            for(l=0;l<=40;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1600+m,615,l);
            }


            for(l=0;l<=30;l++)                              //cloud7
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1770+m,635,l);
            }
            for(l=0;l<=45;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1700+m,625,l);
                draw_circle(1750+m,610,l);
            }
            for(l=0;l<=35;l++)
            {
                glColor3f(0.9,0.9,0.9);
                draw_circle(1745+m,625,l);
            }
                                            //grass
        glColor3f(0.0,0.7,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,160);
        glVertex2f(0,450);
        glVertex2f(1200,450);
        glVertex2f(1200,160);
        glEnd();
        }


                                //plane
   if(plane==1)
{
    float x,y;
    int i;
    GLfloat radius;
    int triangleAmount=40;
    GLfloat twicePi = 2.0*3.1416;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,0.0,0.0);
    x= 1278+n,y=623+o,radius=15;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
        {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
        }
    glEnd();
    glEnd();
    glColor3f(0.0,0.4,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,610+o);
    glVertex2f(1100+n,620+o);
    glVertex2f(1290+n,620+o);
    glVertex2f(1290+n,610+o);
    glEnd();
    glColor3f(0.0,0.4,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,620+o);
    glVertex2f(1150+n,650+o);
    glVertex2f(1290+n,630+o);
    glVertex2f(1290+n,620+o);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,610+o);
    glVertex2f(1130+n,605+o);
    glVertex2f(1290+n,605+o);
    glVertex2f(1290+n,610+o);
    glEnd();
    glColor3f(0.0,0.4,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1290+n,630+o);
    glVertex2f(1290+n,605+o);
    glVertex2f(1330+n,615+o);
    glVertex2f(1330+n,625+o);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1270+n,630+o);
    glVertex2f(1305+n,675+o);
    glVertex2f(1320+n,675+o);
    glVertex2f(1315+n,625+o);
    glEnd();



     glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,0.0,0.0);
    x= 1200+n,y=610+o,radius=10;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
        {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
        }
    glEnd();
     glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,0.0,0.0);
    x= 1230+n,y=610+o,radius=10;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
        {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
        }
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1200+n,600+o);
    glVertex2f(1200+n,620+o);
    glVertex2f(1230+n,620+o);
    glVertex2f(1235+n,600+o);
    glEnd();
}

}
else
{                                    //sky
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,450);
    glVertex2f(0,700);
    glVertex2f(1200,700);
    glVertex2f(1200,450);
    glEnd();

    moon();

    if(fallen_star==1)                              //star1
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(575+p,653+q);
        glVertex2f(570+p,645+q);
        glVertex2f(580+p,645+q);
        glVertex2f(575+p,642+q);
        glVertex2f(570+p,650+q);
        glVertex2f(580+p,650+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(575,653);
        glVertex2f(570,645);
        glVertex2f(580,645);
        glVertex2f(575,642);
        glVertex2f(570,650);
        glVertex2f(580,650);
        glEnd();
     }
    if (fallen_star==2)
     {                                   //star2
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(875-p,643+q);
        glVertex2f(870-p,635+q);
        glVertex2f(880-p,635+q);
        glVertex2f(875-p,632+q);
        glVertex2f(870-p,640+q);
        glVertex2f(880-p,640+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(875,643);
        glVertex2f(870,635);
        glVertex2f(880,635);
        glVertex2f(875,632);
        glVertex2f(870,640);
        glVertex2f(880,640);
        glEnd();
     }
    if (fallen_star==3)                             //star3
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(1175-p,643+q);
        glVertex2f(1170-p,635+q);
        glVertex2f(1180-p,635+q);
        glVertex2f(1175-p,632+q);
        glVertex2f(1170-p,640+q);
        glVertex2f(1180-p,640+q);
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(1175,643);
        glVertex2f(1170,635);
        glVertex2f(1180,635);
        glVertex2f(1175,632);
        glVertex2f(1170,640);
        glVertex2f(1180,640);
     }
    if (fallen_star==4)                                        //star4
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(975+p,643+q);
        glVertex2f(970+p,635+q);
        glVertex2f(980+p,635+q);
        glVertex2f(975+p,632+q);
        glVertex2f(970+p,640+q);
        glVertex2f(980+p,640+q);
        glEnd();

     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(975,643);
        glVertex2f(970,635);
        glVertex2f(980,635);
        glVertex2f(975,632);
        glVertex2f(970,640);
        glVertex2f(980,640);
        glEnd();
     }
    if (fallen_star==5)                                    //star5
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(375-p,698+q);
        glVertex2f(370-p,690+q);
        glVertex2f(380-p,690+q);
        glVertex2f(375-p,687+q);
        glVertex2f(370-p,695+q);
        glVertex2f(380-p,695+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(375,698);
        glVertex2f(370,690);
        glVertex2f(380,690);
        glVertex2f(375,687);
        glVertex2f(370,695);
        glVertex2f(380,695);
        glEnd();
     }
    if (fallen_star==6)                                          //star6
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(750-p,628+q);
        glVertex2f(745-p,620+q);
        glVertex2f(755-p,620+q);
        glVertex2f(750-p,618+q);
        glVertex2f(745-p,625+q);
        glVertex2f(755-p,625+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(750,628);
        glVertex2f(745,620);
        glVertex2f(755,620);
        glVertex2f(750,618);
        glVertex2f(745,625);
        glVertex2f(755,625);
        glEnd();
     }
    if(fallen_star==7)                                    //star7
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(200+p,628+q);
        glVertex2f(195+p,620+q);
        glVertex2f(205+p,620+q);
        glVertex2f(200+p,618+q);
        glVertex2f(195+p,625+q);
        glVertex2f(205+p,625+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(200,628);
        glVertex2f(195,620);
        glVertex2f(205,620);
        glVertex2f(200,618);
        glVertex2f(195,625);
        glVertex2f(205,625);
     }
    if(fallen_star==8)                                     //star8
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(500+p,543+q);
        glVertex2f(495+p,535+q);
        glVertex2f(505+p,535+q);
        glVertex2f(500+p,532+q);
        glVertex2f(495+p,540+q);
        glVertex2f(505+p,540+q);
        glEnd();
     }
    else
     {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(500,543);
        glVertex2f(495,535);
        glVertex2f(505,535);
        glVertex2f(500,532);
        glVertex2f(495,540);
        glVertex2f(505,540);
        glEnd();
     }

    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(300,625,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(400,650,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(1000,675,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(500,590,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(600,645,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(200,665,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(700,680,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(800,600,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(900,635,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(1100,615,l);
        }
    for(l=0;l<=0.5;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(1150,665,l);
        }
    for(l=0;l<=0.9;l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(1025,615,l);
        }

if(plane==1)
{
    float x,y;
    int i;
    GLfloat radius;
    int triangleAmount=40;
    GLfloat twicePi = 2.0*3.1416;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3,0.3,0.3);
    x= 1278+n,y=623+o,radius=15;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
        {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
        }
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,610+o);
    glVertex2f(1100+n,620+o);
    glVertex2f(1290+n,620+o);
    glVertex2f(1290+n,610+o);
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,620+o);
    glVertex2f(1150+n,650+o);
    glVertex2f(1290+n,630+o);
    glVertex2f(1290+n,620+o);
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1100+n,610+o);
    glVertex2f(1130+n,605+o);
    glVertex2f(1290+n,605+o);
    glVertex2f(1290+n,610+o);
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1290+n,630+o);
    glVertex2f(1290+n,605+o);
    glVertex2f(1330+n,615+o);
    glVertex2f(1330+n,625+o);
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1270+n,630+o);
    glVertex2f(1305+n,675+o);
    glVertex2f(1320+n,675+o);
    glVertex2f(1315+n,625+o);
    glEnd();



    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3,0.3,0.3);
    x= 1200+n,y=610+o,radius=10;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
    {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3,0.3,0.3);
    x= 1230+n,y=610+o,radius=10;
    glVertex2f(x,y);
    for(i=0;i<=triangleAmount;i++)
    {
        glVertex2f
        (x+(radius*cos(i*twicePi/triangleAmount)),
        y+(radius*sin(i*twicePi/triangleAmount)));
    }
    glEnd();
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(1200+n,600+o);
    glVertex2f(1200+n,620+o);
    glVertex2f(1230+n,620+o);
    glVertex2f(1235+n,600+o);
    glEnd();
}                             //grass
    glColor3f(0.0,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,160);
    glVertex2f(0,450);
    glVertex2f(1200,450);
    glVertex2f(1200,160);
    glEnd();
}
                                    //road
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(0,0);
glVertex2f(0,250);
glVertex2f(1200,250);
glVertex2f(1200,0);
glEnd();
                                    //road boundary
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(0,240);
glVertex2f(0,260);
glVertex2f(1200,260);
glVertex2f(1200,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(0,240);
glVertex2f(0,260);
glVertex2f(100,260);
glVertex2f(100,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(200,240);
glVertex2f(200,260);
glVertex2f(300,260);
glVertex2f(300,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(400,240);
glVertex2f(400,260);
glVertex2f(500,260);
glVertex2f(500,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(600,240);
glVertex2f(600,260);
glVertex2f(700,260);
glVertex2f(700,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(800,240);
glVertex2f(800,260);
glVertex2f(900,260);
glVertex2f(900,240);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(1000,240);
glVertex2f(1000,260);
glVertex2f(1100,260);
glVertex2f(1100,240);
glEnd();

                                    //road middle line
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(0,120);
glVertex2f(0,130);
glVertex2f(100,130);
glVertex2f(100,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(120,120);
glVertex2f(120,130);
glVertex2f(220,130);
glVertex2f(220,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(240,120);
glVertex2f(240,130);
glVertex2f(340,130);
glVertex2f(340,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(360,120);
glVertex2f(360,130);
glVertex2f(460,130);
glVertex2f(460,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(480,120);
glVertex2f(480,130);
glVertex2f(580,130);
glVertex2f(580,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(600,120);
glVertex2f(600,130);
glVertex2f(700,130);
glVertex2f(700,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(720,120);
glVertex2f(720,130);
glVertex2f(820,130);
glVertex2f(820,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(840,120);
glVertex2f(840,130);
glVertex2f(940,130);
glVertex2f(940,120);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(960,120);
glVertex2f(960,130);
glVertex2f(1060,130);
glVertex2f(1060,120);
glEnd();

                                        //zebra_crossing
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,205);
glVertex2f(1150,235);
glVertex2f(1200,235);
glVertex2f(1200,205);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,170);
glVertex2f(1150,200);
glVertex2f(1200,200);
glVertex2f(1200,170);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,165);
glVertex2f(1150,195);
glVertex2f(1200,195);
glVertex2f(1200,165);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,130);
glVertex2f(1150,160);
glVertex2f(1200,160);
glVertex2f(1200,130);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,95);
glVertex2f(1150,125);
glVertex2f(1200,125);
glVertex2f(1200,95);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,60);
glVertex2f(1150,90);
glVertex2f(1200,90);
glVertex2f(1200,60);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,50);
glVertex2f(1150,85);
glVertex2f(1200,85);
glVertex2f(1200,50);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,15);
glVertex2f(1150,45);
glVertex2f(1200,45);
glVertex2f(1200,15);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(1150,0);
glVertex2f(1150,10);
glVertex2f(1200,10);
glVertex2f(1200,0);
glEnd();


glColor3f(0.8,0.6,0.5);                     //building2
glBegin(GL_POLYGON);
glVertex2f(190,360);
glVertex2f(190,620);
glVertex2f(275,620);
glVertex2f(275,360);
glEnd();
glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
glVertex2f(200,370);
glVertex2f(200,610);
glVertex2f(230,610);
glVertex2f(230,370);
glEnd();
glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
glVertex2f(235,370);
glVertex2f(235,610);
glVertex2f(265,610);
glVertex2f(265,370);
glEnd();
glColor3f(0.8,0.6,0.6);
glBegin(GL_POLYGON);
glVertex2f(275,360);
glVertex2f(275,620);
glVertex2f(485,620);
glVertex2f(485,360);
glEnd();
glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
glVertex2f(285,370);
glVertex2f(285,610);
glVertex2f(325,610);
glVertex2f(325,370);
glEnd();
glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
glVertex2f(335,370);
glVertex2f(335,610);
glVertex2f(375,610);
glVertex2f(375,370);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(385,370);
glVertex2f(385,610);
glVertex2f(425,610);
glVertex2f(425,370);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(435,370);
glVertex2f(435,610);
glVertex2f(475,610);
glVertex2f(475,370);
glEnd();

glColor3f(0.8,0.8,0.8);                    //mosque
glBegin(GL_TRIANGLES);
glVertex2f(645,610);
glVertex2f(665,610);
glVertex2f(655,655);
glEnd();
for(l=0;l<=25;l++)
{
    glColor3f(0.8,0.8,0.8);
    draw_circle(655,600,l);
}
glColor3f(0.8,0.8,0.8);
glBegin(GL_POLYGON);
glVertex2f(635,480);
glVertex2f(635,600);
glVertex2f(675,600);
glVertex2f(675,480);
glEnd();

glColor3f(0.8,0.8,0.8);
glBegin(GL_TRIANGLES);
glVertex2f(435,610);
glVertex2f(455,610);
glVertex2f(445,655);
glEnd();

for(l=0;l<=25;l++)
{
    glColor3f(0.8,0.8,0.8);
    draw_circle(445,600,l);
}
glColor3f(0.8,0.8,0.8);
glBegin(GL_POLYGON);
glVertex2f(425,480);
glVertex2f(425,600);
glVertex2f(465,600);
glVertex2f(465,480);
glEnd();
for(l=0;l<=80;l++)
{
    glColor3f(0.8,0.8,0.8);
    draw_circle(550,470,l);
}
glColor3f(0.7,0.8,0.7);
glBegin(GL_POLYGON);
glVertex2f(350,320);
glVertex2f(350,480);
glVertex2f(750,480);
glVertex2f(750,320);
glEnd();
glColor3f(0.7,0.8,0.6);
glBegin(GL_POLYGON);
glVertex2f(295,320);
glVertex2f(295,480);
glVertex2f(350,480);
glVertex2f(350,320);
glEnd();

for(l=0;l<17;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(322.5,400,l);
}

glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(304.5,360);
glVertex2f(304.5,400);
glVertex2f(340,400);
glVertex2f(340,360);
glEnd();
                                      //door
for(l=0;l<=28;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(550,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(520,320);
glVertex2f(520,400);
glVertex2f(580,400);
glVertex2f(580,320);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(520,390);
glVertex2f(520,395);
glVertex2f(580,395);
glVertex2f(580,390);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(520,320);
glVertex2f(520,395);
glVertex2f(525,395);
glVertex2f(525,320);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(575,320);
glVertex2f(575,395);
glVertex2f(580,395);
glVertex2f(580,320);
glEnd();
	                                   //window
for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(385,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(370,360);
    glVertex2f(370,400);
    glVertex2f(400,400);
    glVertex2f(400,360);
glEnd();

for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(435,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(420,360);
    glVertex2f(420,400);
    glVertex2f(450,400);
    glVertex2f(450,360);
glEnd();

for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(485,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(470,360);
    glVertex2f(470,400);
    glVertex2f(500,400);
    glVertex2f(500,360);
glEnd();

for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(615,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(600,360);
    glVertex2f(600,400);
    glVertex2f(630,400);
    glVertex2f(630,360);
glEnd();

for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(665,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(650,360);
    glVertex2f(650,400);
    glVertex2f(680,400);
    glVertex2f(680,360);
glEnd();
for(l=0;l<=13;l++)
{
    glColor3f(0.3,0.3,0.3);
    draw_circle(715,400,l);
}
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
    glVertex2f(700,360);
    glVertex2f(700,400);
    glVertex2f(730,400);
    glVertex2f(730,360);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(295,320);
glVertex2f(295,325);
glVertex2f(750,325);
glVertex2f(750,320);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(295,320);
glVertex2f(290,300);
glVertex2f(755,300);
glVertex2f(750,320);
glEnd();
                                  //building1
glColor3f(1.0,0.9,0.7);
glBegin(GL_POLYGON);
    glVertex2f(01,320);
    glVertex2f(01,600);
    glVertex2f(50,600);
    glVertex2f(50,320);
glEnd();

glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
    glVertex2f(05,330);
    glVertex2f(05,590);
    glVertex2f(22,590);
    glVertex2f(22,330);
glEnd();

glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
    glVertex2f(27,330);
    glVertex2f(27,590);
    glVertex2f(45,590);
    glVertex2f(45,330);
glEnd();

glColor3f(1.0,0.9,0.8);
glBegin(GL_POLYGON);
    glVertex2f(50,320);
    glVertex2f(50,600);
    glVertex2f(200,600);
    glVertex2f(200,320);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(70,340);
    glVertex2f(70,370);
    glVertex2f(110,370);
    glVertex2f(110,340);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(70,410);
    glVertex2f(70,440);
    glVertex2f(110,440);
    glVertex2f(110,410);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(70,480);
    glVertex2f(70,510);
    glVertex2f(110,510);
    glVertex2f(110,480);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(70,550);
    glVertex2f(70,580);
    glVertex2f(110,580);
    glVertex2f(110,550);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(140,340);
    glVertex2f(140,370);
    glVertex2f(180,370);
    glVertex2f(180,340);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(140,410);
    glVertex2f(140,440);
    glVertex2f(180,440);
    glVertex2f(180,410);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(140,480);
    glVertex2f(140,510);
    glVertex2f(180,510);
    glVertex2f(180,480);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(140,550);
    glVertex2f(140,580);
    glVertex2f(180,580);
    glVertex2f(180,550);
glEnd();

                              //building3
glColor3f(0.5,0.5,0.5);
glBegin(GL_POLYGON);
    glVertex2f(800,320);
    glVertex2f(800,550);
    glVertex2f(925,550);
    glVertex2f(925,320);
glEnd();

glColor3f(0.6,0.6,0.6);
glBegin(GL_POLYGON);
    glVertex2f(925,320);
    glVertex2f(925,550);
    glVertex2f(1195,550);
    glVertex2f(1195,320);
glEnd();

glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1105,500);
    glVertex2f(1105,540);
    glVertex2f(1140,540);
    glVertex2f(1140,500);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1150,500);
    glVertex2f(1150,540);
    glVertex2f(1185,540);
    glVertex2f(1185,500);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1105,450);
    glVertex2f(1105,490);
    glVertex2f(1140,490);
    glVertex2f(1140,450);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1150,450);
    glVertex2f(1150,490);
    glVertex2f(1185,490);
    glVertex2f(1185,450);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1105,400);
    glVertex2f(1105,440);
    glVertex2f(1140,440);
    glVertex2f(1140,400);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1150,400);
    glVertex2f(1150,440);
    glVertex2f(1185,440);
    glVertex2f(1185,400);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1105,350);
    glVertex2f(1105,390);
    glVertex2f(1140,390);
    glVertex2f(1140,350);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
    glVertex2f(1150,350);
    glVertex2f(1150,390);
    glVertex2f(1185,390);
    glVertex2f(1185,350);
glEnd();
glBegin(GL_POLYGON);
    glVertex2f(1105,330);
    glVertex2f(1105,340);
    glVertex2f(1185,340);
    glVertex2f(1185,330);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(805,325);
    glVertex2f(805,545);
    glVertex2f(875,545);
    glVertex2f(875,325);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(875,325);
    glVertex2f(875,480);
    glVertex2f(920,480);
    glVertex2f(920,325);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,470);
    glVertex2f(930,480);
    glVertex2f(1050,480);
    glVertex2f(1050,470);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,460);
    glVertex2f(930,450);
    glVertex2f(1050,450);
    glVertex2f(1050,460);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,440);
    glVertex2f(930,430);
    glVertex2f(1050,430);
    glVertex2f(1050,440);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,420);
    glVertex2f(930,410);
    glVertex2f(1050,410);
    glVertex2f(1050,420);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,400);
    glVertex2f(930,390);
    glVertex2f(1050,390);
    glVertex2f(1050,400);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,380);
    glVertex2f(930,370);
    glVertex2f(1050,370);
    glVertex2f(1050,380);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,360);
    glVertex2f(930,350);
    glVertex2f(1050,350);
    glVertex2f(1050,360);
glEnd();

glColor3f(0.9,1.0,0.9);
glBegin(GL_POLYGON);
    glVertex2f(930,340);
    glVertex2f(930,330);
    glVertex2f(1050,330);
    glVertex2f(1050,340);
glEnd();

glColor3f(0.1,0.1,0.1);
glBegin(GL_POLYGON);
    glVertex2f(1055,325);
    glVertex2f(1055,545);
    glVertex2f(1095,545);
    glVertex2f(1095,325);
glEnd();

glColor3f(0.1,0.1,0.1);
glBegin(GL_POLYGON);
    glVertex2f(955,500);
    glVertex2f(955,490);
    glVertex2f(1050,490);
    glVertex2f(1050,500);
glEnd();

glColor3f(0.1,0.1,0.1);
glBegin(GL_POLYGON);
    glVertex2f(955,520);
    glVertex2f(955,510);
    glVertex2f(1050,510);
    glVertex2f(1050,520);
glEnd();

glColor3f(0.1,0.1,0.1);
glBegin(GL_POLYGON);
    glVertex2f(955,540);
    glVertex2f(955,530);
    glVertex2f(1050,530);
    glVertex2f(1050,540);
glEnd();


                                  //tree1
glColor3f(0.5,0.35,0.05);
glBegin(GL_POLYGON);
glVertex2f(100,270);
glVertex2f(100,370);
glVertex2f(115,370);
glVertex2f(115,270);
glEnd();
	for(l=0;l<=40;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(80,380,l);
		draw_circle(135,380,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(90,430,l);
		draw_circle(125,430,l);
	}
	for(l=0;l<=20;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(107.5,465,l);
	}

                                    //tree4
glColor3f(0.5,0.35,0.05);
glBegin(GL_POLYGON);
glVertex2f(1000,270);
glVertex2f(1000,370);
glVertex2f(1015,370);
glVertex2f(1015,270);
glEnd();
	for(l=0;l<=45;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(980,380,l);
		draw_circle(1035,380,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(980,430,l);
		draw_circle(1035,430,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(985,450,l);
		draw_circle(1030,450,l);
	}
	for(l=0;l<=35;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(1007.5,465,l);
	}

	                                    //tree2
glColor3f(0.5,0.35,0.05);
glBegin(GL_POLYGON);
glVertex2f(320,270);
glVertex2f(320,370);
glVertex2f(335,370);
glVertex2f(335,270);
glEnd();
	for(l=0;l<=45;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(300,380,l);
		draw_circle(355,380,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(300,430,l);
		draw_circle(355,430,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(305,450,l);
		draw_circle(350,450,l);
	}
	for(l=0;l<=35;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(327.5,465,l);
	}
                                    //tree3
glColor3f(0.5,0.35,0.05);
glBegin(GL_POLYGON);
glVertex2f(780,270);
glVertex2f(780,370);
glVertex2f(795,370);
glVertex2f(795,270);
glEnd();
	for(l=0;l<=40;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(760,380,l);
		draw_circle(815,380,l);
	}
	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(770,430,l);
		draw_circle(805,430,l);
	}
	for(l=0;l<=20;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(787.5,465,l);
	}

glColor3f(0.6,0.6,0.6);                     //traffic stand
glBegin(GL_POLYGON);
glVertex2f(1160,260);
glVertex2f(1160,350);
glVertex2f(1170,350);
glVertex2f(1170,260);
glEnd();
glColor3f(0.9,0.9,0.9);
glBegin(GL_POLYGON);
glVertex2f(1140,350);
glVertex2f(1140,500);
glVertex2f(1190,500);
glVertex2f(1190,350);
glEnd();


if(light==1)
    {
    for(l=0;l<=20;l++)
        {
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,475,l);
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,425,l);
        glColor3f(0.2,1.0,0.0);
        draw_circle(1165,375,l);
        }
    }
    else if(light==2)
    {
    for(l=0;l<=20;l++)
        {
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,475,l);
        glColor3f(0.9,0.9,0.0);
        draw_circle(1165,425,l);
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,375,l);
		}
    }
	else
    {
    for(l=0;l<=20;l++)
		{
        glColor3f(1.0,0.0,0.0);
        draw_circle(1165,475,l);
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,425,l);
        glColor3f(0.0,0.0,0.0);
        draw_circle(1165,375,l);
		}
    }



glColor3f(0.9,1,0.5);               //car0
glBegin(GL_POLYGON);
glVertex2f(1205+j,200);
glVertex2f(1210+j,300);
glVertex2f(1255+j,390);
glVertex2f(1295+j,400);
glVertex2f(1750+j,400);
glVertex2f(1760+j,300);
glVertex2f(1750+j,220);
glVertex2f(1650+j,200);
glVertex2f(1350+j,200);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(1250+j,380);
glVertex2f(1720+j,380);
glVertex2f(1720+j,300);
glVertex2f(1355+j,300);
glVertex2f(1295+j,230);
glVertex2f(1206+j,230);
glVertex2f(1210+j,300);
glEnd();


glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1230+j,300);
glVertex2f(1233+j,300);
glVertex2f(1233+j,200);
glVertex2f(1230+j,200);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1290+j,300);
glVertex2f(1293+j,300);
glVertex2f(1293+j,200);
glVertex2f(1290+j,200);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1230+j,297);
glVertex2f(1290+j,297);
glVertex2f(1290+j,300);
glVertex2f(1230+j,300);
glEnd();


glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1330+j,250);
glVertex2f(1700+j,250);
glVertex2f(1700+j,253);
glVertex2f(1330+j,253);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1697+j,250);
glVertex2f(1700+j,250);
glVertex2f(1700+j,209);
glVertex2f(1697+j,209);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1330+j,250);
glVertex2f(1333+j,250);
glVertex2f(1333+j,200);
glVertex2f(1330+j,200);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1450+j,250);
glVertex2f(1453+j,250);
glVertex2f(1453+j,200);
glVertex2f(1450+j,200);
glEnd();
glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);
glVertex2f(1580+j,250);
glVertex2f(1583+j,250);
glVertex2f(1583+j,200);
glVertex2f(1580+j,200);
glEnd();


for(l=0;l<40;l++)
   {
	glColor3f(0.0,0.0,0.0);
	draw_circle(1350+j,200,l);
	draw_circle(1600+j,200,l);
   }
for(l=0;l<28;l++)
   {
	glColor3f(0.5,0.5,0.5);
	draw_circle(1350+j,200,l);
	draw_circle(1600+j,200,l);
   }

                                       //car2

glColor3f(0.9,0.9,0.9);
glBegin(GL_POLYGON);
glVertex2f(-25+i,135);
glVertex2f(-10+i,210);
glVertex2f(230+i,210);
glVertex2f(260+i,135);
glEnd();

glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(-10+i,130);
glVertex2f(5+i,195);
glVertex2f(35+i,195);
glVertex2f(35+i,130);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(45+i,130);
glVertex2f(45+i,195);
glVertex2f(140+i,195);
glVertex2f(140+i,130);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(150+i,130);
glVertex2f(150+i,195);
glVertex2f(220+i,195);
glVertex2f(250+i,130);
glEnd();




glColor3f(0.9,0.9,0.9);
glBegin(GL_POLYGON);
glVertex2f(-25+i,135);
glVertex2f(260+i,135);
glVertex2f(350+i,115);
glVertex2f(350+i,105);
glVertex2f(-25+i,105);
glEnd();

glColor3f(0.9,0.9,0.9);
glBegin(GL_POLYGON);
glVertex2f(-25+i,105);
glVertex2f(-10+i,55);
glVertex2f(285+i,55);
glVertex2f(285+i,105);
glEnd();

glColor3f(0.9,0.9,0.9);
glBegin(GL_POLYGON);
glVertex2f(285+i,105);
glVertex2f(285+i,55);
glVertex2f(360+i,60);
glVertex2f(350+i,105);
glEnd();
for(l=0;l<33;l++)
   {
	glColor3f(0.0,0.0,0.0);
	draw_circle(60+i,55,l);
	draw_circle(240+i,55,l);
   }
for(l=0;l<25;l++)
   {
	glColor3f(0.7,0.7,0.7);
	draw_circle(60+i,55,l);
	draw_circle(240+i,55,l);
   }

                            //car3
glColor3f(0.0,0.0,.0);
glBegin(GL_POLYGON);
glVertex2f(-550+i,25);
glVertex2f(-550+i,35);
glVertex2f(-100+i,35);
glVertex2f(-100+i,25);
glEnd();

glColor3f(1.0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-550+i,35);
glVertex2f(-600+i,55);
glVertex2f(-150+i,55);
glVertex2f(-100+i,35);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-550+i,35);
glVertex2f(-600+i,55);
glVertex2f(-150+i,55);
glVertex2f(-100+i,35);
glEnd();

glColor3f(1,0,0);
glBegin(GL_POLYGON);
glVertex2f(-550+i,55);
glVertex2f(-630+i,65);
glVertex2f(-180+i,65);
glVertex2f(-150+i,55);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-550+i,55);
glVertex2f(-630+i,65);
glVertex2f(-180+i,65);
glVertex2f(-150+i,55);
glEnd();

glColor3f(1.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(-570+i,65);
glVertex2f(-640+i,85);
glVertex2f(-500+i,85);
glVertex2f(-500+i,65);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-570+i,65);
glVertex2f(-640+i,85);
glVertex2f(-500+i,85);
glVertex2f(-500+i,65);
glEnd();

glColor3f(1.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(-590+i,85);
glVertex2f(-650+i,95);
glVertex2f(-500+i,95);
glVertex2f(-500+i,85);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-590+i,85);
glVertex2f(-650+i,95);
glVertex2f(-500+i,95);
glVertex2f(-500+i,85);
glEnd();

glColor3f(1.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(-470+i,105);
glVertex2f(-640+i,95);
glVertex2f(-500+i,95);
glVertex2f(-500+i,105);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-470+i,105);
glVertex2f(-640+i,95);
glVertex2f(-500+i,95);
glVertex2f(-500+i,105);
glEnd();

glColor3f(1.0,0.0,.0);
glBegin(GL_POLYGON);
glVertex2f(-590+i,115);
glVertex2f(-650+i,105);
glVertex2f(-500+i,105);
glVertex2f(-500+i,115);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-590+i,115);
glVertex2f(-650+i,105);
glVertex2f(-500+i,105);
glVertex2f(-500+i,115);
glEnd();

glColor3f(1.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(-650+i,135);
glVertex2f(-500+i,115);
glVertex2f(-500+i,65);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-650+i,135);
glVertex2f(-500+i,115);
glVertex2f(-500+i,65);
glEnd();

glColor3f(0,0,1);
glBegin(GL_POLYGON);
glVertex2f(-500+i,65);
glVertex2f(-500+i,115);
glVertex2f(-400+i,135);
glVertex2f(-400+i,65);
glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(-500+i,65);
glVertex2f(-500+i,115);
glVertex2f(-400+i,135);
glVertex2f(-400+i,65);
glEnd();

glColor3f(0.0,0.0,1.0);
glBegin(GL_POLYGON);
glVertex2f(-390+i,105);
glVertex2f(-390+i,75);
glVertex2f(-220+i,75);
glVertex2f(-260+i,105);
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(-400+i,115);
glVertex2f(-400+i,65);
glVertex2f(-180+i,65);
glVertex2f(-250+i,115);
glEnd();

for(l=0;l<40;l++)
   {
	glColor3f(0.0,0.0,0.0);
	draw_circle(-480+i,50,l);
   }
for(l=0;l<30;l++)
   {
	glColor3f(0.6,0.6,0.6);
	draw_circle(-480+i,50,l);
   }
 for(l=0;l<30;l++)
   {
	glColor3f(0.0,0.0,0.0);
	draw_circle(-230+i,40,l);
   }

for(l=0;l<20;l++)
   {
	glColor3f(0.6,0.6,0.6);
	draw_circle(-230+i,40,l);
   }

                                       //car1
glColor3f(0.9,0.8,0.0);
glBegin(GL_POLYGON);
glVertex2f(485+i,150);
glVertex2f(480+i,135);
glVertex2f(895+i,135);
glVertex2f(890+i,150);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(480+i,135);
glVertex2f(480+i,105);
glVertex2f(895+i,105);
glVertex2f(895+i,135);
glEnd();
glColor3f(0.9,0.8,0.0);
glBegin(GL_POLYGON);
glVertex2f(480+i,105);
glVertex2f(495+i,55);
glVertex2f(790+i,55);
glVertex2f(790+i,105);
glEnd();
glColor3f(0.9,0.8,0.0);
glBegin(GL_POLYGON);
glVertex2f(790+i,105);
glVertex2f(790+i,55);
glVertex2f(890+i,75);
glVertex2f(895+i,105);
glEnd();

glColor3f(0.9,0.8,0.0);
glBegin(GL_POLYGON);
glVertex2f(550+i,150);
glVertex2f(580+i,220);
glVertex2f(710+i,220);
glVertex2f(780+i,150);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(555+i,150);
glVertex2f(585+i,215);
glVertex2f(645+i,215);
glVertex2f(645+i,150);
glEnd();
glColor3f(0.2,0.2,0.2);
glBegin(GL_POLYGON);
glVertex2f(650+i,150);
glVertex2f(650+i,215);
glVertex2f(705+i,215);
glVertex2f(775+i,150);
glEnd();



for(l=0;l<35;l++)
   {
	glColor3f(0.0,0.0,0.0);
	draw_circle(580+i,55,l);
	draw_circle(750+i,55,l);
   }
for(l=0;l<27;l++)
   {
	glColor3f(0.6,0.6,0.6);
	draw_circle(580+i,55,l);
	draw_circle(750+i,55,l);
   }

glFlush();
}

void myMouseFunc( int button, int state, int x, int y )
{
    if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
    {
        float xPos = ((float)x)/((float)(winWidth));
        float yPos = ((float)y)/((float)(winHeight));
        printf("X %.2f ", xPos);
        printf("Y %.2f\n", yPos);

        if(day == 0 && ((xPos>0.47 && xPos< 0.49) && (yPos > 0.06 && yPos < 0.8))
                    ||((xPos>0.76 && xPos< 0.78) && (yPos > 0.10 && yPos < 0.12)))
            {
            fallen_star=1;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.72 && xPos< 0.74) && (yPos > 0.06 && yPos < 0.8))
                    ||((xPos>1.16 && xPos< 1.18) && (yPos > 0.12 && yPos < 0.14)))
            {
            fallen_star=2;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.97 && xPos< 0.99) && (yPos > 0.08 && yPos < 0.10))
                    ||((xPos>1.56 && xPos< 1.58) && (yPos > 0.12 && yPos < 0.14)))
            {
            fallen_star=3;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.80 && xPos< 0.82) && (yPos > 0.08 && yPos < 0.10))
                    ||((xPos>1.29 && xPos< 1.31) && (yPos > 0.12 && yPos < 0.14)))
            {
            fallen_star=4;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.30 && xPos< 0.32) && (yPos > 0.00 && yPos < 0.02))
                    ||((xPos>0.49 && xPos< 0.51) && (yPos > 0.01 && yPos < 0.03)))
            {
            fallen_star=5;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.61 && xPos< 0.63) && (yPos > 0.10 && yPos < 0.12))
                    ||((xPos>0.99 && xPos< 1.01) && (yPos > 0.15 && yPos < 0.17)))
            {
            fallen_star=6;
            p=q=0;
            }
        if(day == 0 && ((xPos>0.16 && xPos< 0.18) && (yPos > 0.10 && yPos < 0.12))
                    ||((xPos>0.25 && xPos< 0.27) && (yPos > 0.15 && yPos < 0.17)))
            {
            fallen_star=7;
            p=q=0;
            }
         if(day == 0 && ((xPos>0.41 && xPos< 0.43) && (yPos > 0.22 && yPos < 0.24))
                     ||((xPos>0.66 && xPos< 0.68) && (yPos > 0.32 && yPos < 0.34)))
            {
            fallen_star=8;
            p=q=0;
            }
     glutPostRedisplay();
    }
}

void idle()
{
glClearColor(1.0,1.0,1.0,1.0);
if(light==0 && ( j<=-10 && j>=-1755))
 {
     j-=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
 if(light==0)
 {
	 j=j;
	 m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
 else
 {
     j-=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }

if(light==0 && (i>=0 && i<=240))
 {
     i+=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
if(light==0 && (i>=250 && i<=760))
 {
     i+=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
if(light==0 && (i>=795 && i<=1230))
 {
	 i+=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
if(light==0 && (i>=1240 && 1560))
 {
	 i+=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
if(light==0)
 {
	 i=i;
	 m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
else if(light==2 && (i>=330 && i<=750))
 {
     i+=SPEED/20;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
else if(light==2 && (i>=830 && i<=1100))
 {
	 i+=SPEED/20;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
else if(light==2 && (i>=1200 && i<=1620))
 {
	 i+=SPEED/20;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
else if(light==2)
 {
	 i+=SPEED/20;
	 m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }
else
 {
     i+=SPEED/10;
     m-=0.5;
     n-=2;
	 o+=0.2;
	 p+=3;
     q-=0.3;
 }

if(i>1750)
	 i=0;
if(j<-1800)
     j=0;
if(m<-800)
	 m=0;
if( o>90 && n<140)
 {
	plane=0;
 }
if (day==0 &&(b<=100&& b>=-100))
{
        b-=0.5;
}
if (day==1 &&(a<=100&& a>=-200))
{
        a-=0.5;
}
glutPostRedisplay();
}
void keyboardFunc( unsigned char key, int x, int y )
{
switch( key )
    {
    case 'g':
    case 'G':
        light=1;
    break;
    case 'y':
    case 'Y':
        light=2;
    break;
	case 'r':
	case 'R':
		light=0;
    break;
    case 'd':
	case 'D':
		day=1;
		a=0;
    break;
	case 'n':
    case 'N':
		day=0;
		b=0;
    break;
    };
glutPostRedisplay();
}
void main_menu(int index)
{
	switch(index)
	{
	case 1:
	if(index==1)
	 {
        plane=1;
		 o=n=0;
	 }
	break;
	case 2:
	if (index==2)
    {
        fallen_star=1;
        p=q=0.0;
    }
    break;
    case 3:
	if (index==3)
    {
        fallen_star=2;
        p=q=0.0;
    }
    break;
    case 4:
        if (index==4);
        {
            raining=0;
        }
    break;
        case 5:
        if (index==5);
        {
            raining=1;
        }
    break;

	case 6:
        if(index==6)
        {
            exit(0);
        }
    break;
	}
glutPostRedisplay();
}
void myinit()
{
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(0.0,0.0,1.0);
glPointSize(2.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
draw_object();
drawRain();
glFlush();
glutPostRedisplay();
}
int main(int argc,char*argv[])
{
int c_menu;
    printf("\n");
    printf(" |===========================================================|\n");
    printf(" |---Computer Graphics Project:- 'Simulation of City view'---|\n");
    printf(" |===========================================================|\n");
    printf(" |                                                           |\n");
    printf(" |----Help Center (How to Operate ?) ------------------------|\n");
	printf(" |    > Press 'r' or 'R' for Red signal light                |\n");
	printf(" |    > Press 'g' or 'G' for Green  signal light             |\n");
	printf(" |    > Press 'y' or 'Y' for Yellow  signal light            |\n");
	printf(" |    > Press 'd' or 'D' for Day                             |\n");
	printf(" |    > Press 'n' or 'N' for Night                           |\n");
	printf(" |    > Press RIGHT MOUSE BUTTON to display menu             |\n");
	printf(" |       > Select  'Aeroplane' for moving Aeroplane          |\n");
	printf(" |       > Select  'Fallen_Star1' for moving star            |\n");
	printf(" |       > Select  'Fallen_Star2' for moving star            |\n");
	printf(" |       > Select  'Rain' for raining                        |\n");
	printf(" |       > Select  'Stop_Rain' for stopping rain             |\n");
	printf(" |       > Select  'Quit' to exit the application            |\n");
	printf(" | > Press LEFT MOUSE BUTTON on stars to display Fallen star |\n");
	printf(" |                                                           |\n");
	printf(" |===========================================================|\n");
	printf(" |----------------------TEAM INEVITABLE----------------------|\n");
    printf(" |===========================================================|\n");
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(250,0);
	glutCreateWindow("CITY_VIEW");
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(myMouseFunc);
	glutKeyboardFunc(keyboardFunc);
	c_menu=glutCreateMenu(main_menu);
	glutAddMenuEntry("plane",1);
	glutAddMenuEntry("fallen_star",2);
	glutAddMenuEntry("fallen_star",3);
	glutAddMenuEntry("rain",4);
	glutAddMenuEntry("strop_rain",5);
	glutAddMenuEntry("Quite",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();
	return 0;
}
