#ifndef _SWITCH_TECHNIQUE_HANDLER_H
#define _SWITCH_TECHNIQUE_HANDLER_H

namespace osgExample {

// std
#include <iostream>

// osg
#include <osg/ref_ptr>
#include <osg/Switch>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

class SwitchInstancingHandler : public osgGA::GUIEventHandler
{
public:
	typedef osg::ref_ptr<osg::Switch> (*SetupSceneFuncPtr)(unsigned int, unsigned int, GLint);

	SwitchInstancingHandler(osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Switch> switchNode, GLint maxInstanceMatrices, SetupSceneFuncPtr setupScene)
		:	m_viewer(viewer),
			m_switch(switchNode),
			m_size(64.0f),
			m_maxInstanceMatrices(maxInstanceMatrices),
			m_setupScene(setupScene)
	{
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (ea.getEventType() == osgGA::GUIEventAdapter::KEYUP)
		{
			switch(ea.getKey())
			{
			case osgGA::GUIEventAdapter::KEY_1:
				m_switch->setSingleChildOn(0);
				m_switch->setValue(3, true);
				std::cout << "Switched to software instancing" << std::endl;
				return true;
				break;
			case osgGA::GUIEventAdapter::KEY_2:
				m_switch->setSingleChildOn(1);
				m_switch->setValue(3, true);
				std::cout << "Switched to hardware instancing with uniforms" << std::endl;
				return true;
				break;
			case osgGA::GUIEventAdapter::KEY_3:
				m_switch->setSingleChildOn(2);
				m_switch->setValue(3, true);
				std::cout << "Switched to hardware instancing with textures" << std::endl;
				return true;
				break;
			case osgGA::GUIEventAdapter::KEY_Plus:
				m_size *= 2.0f;
				m_size = std::min(std::max(m_size, 8.0f), 512.0f);
				m_switch = m_setupScene((unsigned int)m_size, (unsigned int)m_size, m_maxInstanceMatrices);
				m_viewer->setSceneData(m_switch);
				std::cout << "Increased scene size to " << m_size << "x" << m_size << std::endl;
				return true;
				break;
			case osgGA::GUIEventAdapter::KEY_Minus:
				m_size *= 0.5f;
				m_size = std::min(std::max(m_size, 8.0f), 512.0f);
				m_switch = m_setupScene((unsigned int)m_size, (unsigned int)m_size, m_maxInstanceMatrices);
				m_viewer->setSceneData(m_switch);
				std::cout << "Decreased scene size to " << m_size << "x" << m_size << std::endl;
				return true;
				break;
			default:
				break;
			}

		}

		return false;
	}
private:
	osg::ref_ptr<osg::Switch>		m_switch;
	osg::ref_ptr<osgViewer::Viewer> m_viewer;
	float							m_size;
	GLint							m_maxInstanceMatrices;

	SetupSceneFuncPtr				m_setupScene;
};

}
#endif
