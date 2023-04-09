#include "Object.h"

void Sphere::Draw() {
	int cnt = 0;
	glBegin(GL_QUAD_STRIP);

	for (int i = -90; i < 90; i += 10) {
		float di = rad(i);
		float di1 = rad(i + 10);
		for (int j = 0; j <= 360; j += 10) {
			float dj = rad(j);
			glTexCoord2f((sin(dj) * cos(di)) / 2 + 0.5, sin(di) / 2 + 0.5);
			glVertex3f(sin(dj) * cos(di), sin(di), cos(di) * cos(dj));
			glTexCoord2f((sin(dj) * cos(di1)) / 2 + 0.5, sin(di1) / 2 + 0.5);
			glVertex3f(sin(dj) * cos(di1), sin(di1), cos(di1) * cos(dj));
		}
	}
	glEnd();
}


void Cylinder::Draw() {
	float texPos = 0;
	float texStep = 1.0 / 360;
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 360; i += 10) {
		float d = rad(i);
		glTexCoord2f(texPos, 0);
		glVertex3f(cos(d), 1, sin(d));
		glTexCoord2f(texPos, 1);
		glVertex3f(cos(d), -1, sin(d));
		texPos += texStep * 10;
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i <= 360; i += 10) {
		float d = rad(i);
		float d1 = rad(i + 10);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, -1, 0);
		glTexCoord2f(cos(d) / 2 + 0.5, sin(d) / 2 + 0.5);
		glVertex3f(cos(d), -1, sin(d));
		glTexCoord2f(cos(d1) / 2 + 0.5, sin(d1) / 2 + 0.5);
		glVertex3f(cos(d1), -1, sin(d1));

		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 1, 0);
		glTexCoord2f(cos(d) / 2 + 0.5, sin(d) / 2 + 0.5);
		glVertex3f(cos(d), 1, sin(d));
		glTexCoord2f(cos(d1) / 2 + 0.5, sin(d1) / 2 + 0.5);
		glVertex3f(cos(d1), 1, sin(d1));
	}
	glEnd();
}