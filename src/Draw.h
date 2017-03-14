#ifndef LIBRENDER_DRAW_H
# define LIBRENDER_DRAW_H

# include "Texture.h"
# include "Color.h"

namespace librender
{

	void drawColorQuadBegin();
	void drawColorQuadEnd();
	void drawColorQuadPart(int x, int y, int width, int height, Color &topLeft, Color &topRight, Color &bottomRight, Color &bottomLeft);
	void drawColorQuadPart(int x, int y, int width, int height, Color &color);
	void drawColorQuad(int x, int y, int width, int height, Color &topLeft, Color &topRight, Color &bottomRight, Color &bottomLeft);
	void drawColorQuad(int x, int y, int width, int height, Color &color);
	void drawColorQuadBorderBegin(float lineWidth = 1);
	void drawColorQuadBorderEnd();
	void drawColorQuadBorderPart(int x, int y, int width, int height, Color &topLeftColor, Color &topRightColor, Color &bottomRightColor, Color &bottomLeftColor);
	void drawColorQuadBorderPart(int x, int y, int width, int height, Color &color);
	void drawColorQuadBorder(int x, int y, int width, int height, Color &topLeftColor, Color &topRightColor, Color &bottomRightColor, Color &bottomLeftColor, float lineWeight = 1);
	void drawColorQuadBorder(int x, int y, int width, int height, Color &color, int lineWeight = 1);
	void drawQuadBegin(Texture *texture);
	void drawQuadEnd();
	void drawQuadPart(Texture *texture, int x, float y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight);
	void drawQuadPart(Texture *texture, int x, float y, int width, int height);
	void drawQuadPart(Texture *texture, int x, float y);
	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, Color &color);
	void drawQuad(Texture *texture, int x, int y, int width, int height, int texXOrg, int texYOrg, int texCoWidth, int texCoHeight, float alpha = 1);
	void drawQuad(Texture *texture, int x, int y, int width, int height, Color &color);
	void drawQuad(Texture *texture, int x, int y, int width, int height, float alpha = 1);
	void drawQuad(Texture *texture, int x, int y, Color &color);
	void drawQuad(Texture *texture, int x, int y, float alpha = 1);
	void drawCircleBegin(float lineWidth = 1);
	void drawCircleEnd();
	void drawCirclePart(int x, int y, int rayon, int nbSeg, float angle, float startAngle);
	void drawCirclePart(int x, int y, int rayon, int nbSeg);
	void drawCirclePart(int x, int y, int rayon);
	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWidth, float angle, float startAngle);
	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg, float lineWidth);
	void drawCircle(int x, int y, int rayon, Color &color, int nbSeg);
	void drawCircle(int x, float y, int rayon, Color &color);
	void drawLineBegin(float lineWidth);
	void drawLineEnd();
	void drawLinePart(int x1, int y1, int x2, int y2, Color &color1, Color &color2);
	void drawLinePart(int x1, int y1, int x2, int y2, Color &color1);
	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2, float lineWidth);
	void drawLine(int x1, int y1, int x2, int y2, Color &color1, Color &color2);
	void drawLine(int x1, int y1, int x2, int y2, Color &color, float lineWidth);
	void drawLine(int x1, int y1, int x2, int y2, Color &color);
	void drawPointBegin(float size = 1);
	void drawPointEnd();
	void drawPointPart(int x, int y, Color &color);
	void drawPoint(int x, int y, Color &color, float size);
	void drawPoint(float x, float y, Color &color);

}

#endif
