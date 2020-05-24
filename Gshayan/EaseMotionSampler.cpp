#include "EaseMotionSampler.h"
#include <iostream>





EaseMotionSampler::~EaseMotionSampler()
{
}



EaseMotionSampler::EaseMotionSampler(osg::Matrix start, const osg::Vec3 & pos) :_previous(0.0f), _pos(pos), _start(start)
{
	//std::cout <<"EaseMotionSampler::EaseMotionSampler=" <<_start.getTrans().x()<< std::endl; 
}

void EaseMotionSampler::operator()(osg::Node * node, osg::NodeVisitor * nv)
{
	std::cout << "Ea llopp    ler=" << _start.getTrans().x() << std::endl;
	if (!_motion.valid()) {
		std::cout << "_!nmoysioerogsdbnffsdfg" << std::endl; return;
	}

	osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(node);

	if (!mt) return;

	double t = nv->getFrameStamp()->getSimulationTime();

	// This avoids a little glitch when the animation doesn't start right away
	// when the application is launched.
	if (_previous == 0.0f) _previous = t;

	_motion->update(t - _previous);

	_previous = t;
	osg::Matrix m;
	// _pos * _motion->getValue()));
	m.setTrans(_start.getTrans() + (_pos * _motion->getValue()));
	//m.setRotate(_start.getRotate()* osg::Quat(.20*_motion->getValue(), 1, 0, 0));
	//mt->setMatrix(mt->getMatrix().translate(_pos * _motion->getValue()));
	//std::cout << " motion=" << _motion->getValue() << std::endl;
 //m.translate(_pos * _motion->getValue());

 //
	std::cout << "t - _previous=" << _motion->getTime() << "\t _DURATION=" << _DURATION << std::endl;
	//	if (_motion->getTime() >= _DURATION) _motion = NULL;
	mt->setMatrix(m);

}



	template<typename T>
	void EaseMotionSampler::setMotion() {

		_motion = new T(M_START, M_DURATION, M_CHANGE, osgAnimation::Motion::LOOP);
		_DURATION= M_DURATION;
	}
	
		//// Normally, check to make sure we have an update
		//// visitor, not necessary in this simple example.
		//osg::MatrixTransform* mtLeft =
		//	dynamic_cast<osg::MatrixTransform*>(node);
		//osg::Matrix mR, mT;
		//mT.makeTranslate(-6., 0., 0.);
		//mR.makeRotate(_angle, osg::Vec3(0., 0., 1.));
		//mtLeft->setMatrix(mR * mT);
		//// Increment the angle for the next from.
		//_angle += 0.01;
		//// Continue traversing so that OSG can process
		//// any other nodes with callbacks.
		//traverse(node, nv);
	

