#include "stdafx.h"
#include "TravelManipulator.h"

// ���캯��
TravelManipulator::TravelManipulator():m_fMoveSpeed(1.0f),
	m_bLeftButtonDown(false),
	m_fpushX(0),
	m_fAngle(2.5),
	m_bPeng(true),
	m_fpushY(0)
{
	m_vPosition = osg::Vec3(-22.0f, -274.0f, 100.0f);
	m_vRotation = osg::Vec3(osg::PI_2, 0.0f, 0.0f);
}

TravelManipulator::~TravelManipulator(void)
{
}

// �����������ӵ�������
TravelManipulator *TravelManipulator::TravelToScence(osg::ref_ptr<osgViewer::Viewer> viewer)
{
	TravelManipulator* camera = new TravelManipulator;

	viewer->setCameraManipulator(camera);

	camera->m_pHostViewer = viewer;

	return camera;
}

// ���þ���
void TravelManipulator::setByMatrix(const osg::Matrix &matrix)
{

}

// ����������
void TravelManipulator::setByInverseMatrix(const osg::Matrix &matrix)
{

}

// �õ�����
osg::Matrixd TravelManipulator::getMatrix(void)const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return mat * osg::Matrixd::translate(m_vPosition);

}

// �õ�������
osg::Matrixd TravelManipulator::getInverseMatrix(void) const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
}

// �¼���������
bool TravelManipulator::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us)
{
	// ��ȡ����λ��
	float mouseX = ea.getX();
	float mouseY = ea.getY();

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			// �ո���
			if(ea.getKey() == 0x20)
			{
				us.requestRedraw();
				us.requestContinuousUpdate(false);

				return true;

			}

			// ���Ƽ�
			if (ea.getKey() == 0xFF50)
			{
				ChangePosition(osg::Vec3(0, 0, m_fMoveSpeed));

				return true;
			}

			// ���Ƽ�
			if (ea.getKey() == 0xFF57)
			{
				ChangePosition(osg::Vec3(0, 0, -m_fMoveSpeed));

				return true;
			}

			// ����
			if (ea.getKey() == 0x2B)
			{
				m_fMoveSpeed += 1.0f;

				return true;
			}

			// �����ٶ�
			if (ea.getKey() == 0x2D)
			{
				m_fMoveSpeed -= 0.1f;

				if(m_fMoveSpeed < 1.0f)
				{
					m_fMoveSpeed = 1.0f;
				}

				return true;
			}

			// ǰ��
			if (ea.getKey() == 0xFF52 || ea.getKey() == 0x57 || ea.getKey() == 0x77)
			{
				ChangePosition(osg::Vec3(0, m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]),0,0));

				return true;
			}

			// ����
			if (ea.getKey() == 0xFF54 || ea.getKey() == 0x53 || ea.getKey() == 0x73)
			{
				ChangePosition(osg::Vec3(0, -m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]),0,0));

				return true;
			}

			// ����
			if (ea.getKey() == 0x41 || ea.getKey() == 0x61)
			{
				ChangePosition(osg::Vec3(0, m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]),0));
				ChangePosition(osg::Vec3(-m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]),0,0));

				return true;
			}

			// ����
			if (ea.getKey() == 0x44 || ea.getKey() == 0x64)
			{
				ChangePosition(osg::Vec3(0, -m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]),0));
				ChangePosition(osg::Vec3(m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]),0,0));

				return true;
			}

			// ����ת
			if (ea.getKey() == 0xFF53)
			{
				m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
			}

			// ����ת
			if (ea.getKey() == 0xFF51)
			{
				m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
			}

			// �ı���Ļ�Ƕ�F��
			if (ea.getKey() == 0x46 || ea.getKey() == 0x66)
			{
				m_fAngle -= 0.2;

				return true;
			}

			//G��
			if (ea.getKey() == 0x47 || ea.getKey() == 0x66)
			{
				m_fAngle += 0.2;

				return true;
			}

			return true;
		}

	case(osgGA::GUIEventAdapter::PUSH):

		if (ea.getButton() == 1)
		{
			m_fpushX = mouseX;
			m_fpushY = mouseY;

			m_bLeftButtonDown = true;
		}

		return true;

		// �϶�
	case(osgGA::GUIEventAdapter::DRAG):

		if (m_bLeftButtonDown)
		{
			m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle * (mouseX - m_fpushX)) / 200;
			m_vRotation._v[0] -= osg::DegreesToRadians(1.1 * (mouseY - m_fpushY)) / 200;

			if (m_vRotation._v[0] >= 3.14)
			{
				m_vRotation._v[0] = 3.14;
			}

			if (m_vRotation._v[0] <= 0)
			{
				m_vRotation._v[0] = 0;
			}
		}

		return false;

		// �����ͷ�
	case(osgGA::GUIEventAdapter::RELEASE):

		if (ea.getButton() == 1)
		{
			m_bLeftButtonDown = false;
		}

		return false;

	default:

		return false;
	}

}

// λ�ñ任����
void TravelManipulator::ChangePosition(osg::Vec3 &delta)
{
	// ��ײ����
	if (m_bPeng)
	{
		// �õ��µ�λ��
		osg::Vec3 newPos1 = m_vPosition + delta;

		osgUtil::IntersectVisitor ivXY;

		// �����µ�λ�õõ������߶μ���
		osg::ref_ptr<osg::LineSegment>lineXY = new osg::LineSegment(newPos1, m_vPosition);

		osg::ref_ptr<osg::LineSegment>lineZ = new osg::LineSegment(newPos1 + osg::Vec3(0.0f, 0.0f, 10.0f), newPos1 - osg::Vec3(0.0f, 0.0f, -10.0f));

		ivXY.addLineSegment(lineZ.get());
		ivXY.addLineSegment(lineXY.get());

		// �ṹ��������
		m_pHostViewer->getSceneData()->accept(ivXY);

		// ����û����ײ
		if (!ivXY.hits())
		{
			m_vPosition += delta;
		}

	}
	else
	{
		m_vPosition += delta;
	}
}

// �����ٶ�
void TravelManipulator::setSpeed(float &sp)
{
	m_fMoveSpeed = sp;
}

// ���õ�ǰ�ٶ�
float TravelManipulator::getSpeed()
{
	return m_fMoveSpeed;
}

// ������ʼ��λ��
void TravelManipulator::SetPosition(osg::Vec3 &position)
{
	m_vPosition = position;
}

// �õ���ǰ����λ��
osg::Vec3 TravelManipulator::GetPosition()
{
	return m_vPosition;
}
