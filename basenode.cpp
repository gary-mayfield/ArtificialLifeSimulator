#include "basenode.h"

BaseNode::BaseNode()
{
}

void BaseNode::updateCircleTable(float radius, float x, float y)
{
    QSGGeometry *g = geometry();

    if((unsigned int)g->vertexCount() != unitCircleTableX.size())
        g->allocate(unitCircleTableX.size());

    QSGGeometry::TexturedPoint2D *v = g->vertexDataAsTexturedPoint2D();

    for(size_t i=0; i<unitCircleTableX.size(); ++i){
        v[i].set(unitCircleTableX[i]*radius+x, unitCircleTableY[i]*radius+y,
                 (unitCircleTableX[i]+1)/2,(unitCircleTableY[i]+1)/2);
    }
}

void BaseNode::initCircleTable(){

    const unsigned HALF_PREC = 10;
    const float angInc = M_PI / static_cast<float>(HALF_PREC);
    const float cosInc = cos(angInc);
    const float sinInc = sin(angInc);

    float xc = 1.0f;
    float yc = 0.0f;

    unitCircleTableX.clear();
    unitCircleTableY.clear();

    unitCircleTableX.push_back(xc);
    unitCircleTableY.push_back(yc);

    for (unsigned int iAng=1; iAng<HALF_PREC; ++iAng)  {
        float xcNew = cosInc * xc - sinInc * yc;
        yc = sinInc * xc + cosInc * yc;
        xc = xcNew;
        unitCircleTableX.push_back(xc);
        unitCircleTableY.push_back(yc);

        unitCircleTableX.push_back(xc);
        unitCircleTableY.push_back(-yc);
    }

    unitCircleTableX.push_back(0.0f);
    unitCircleTableY.push_back(1.0f);
}

