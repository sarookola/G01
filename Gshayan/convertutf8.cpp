#include "convertutf8.h"



int convertutf8::CalcChar(int id, bool prev, bool next)
{
	if (prev && next)
		return id;
	else if (next)
		return id - 1;
	else if (prev)
		return id - 2;
	else
		return id - 3;

} // CalcChar

osgText::String convertutf8::Convertp(osgText::String m_pText, int direction)
{

	int pch = 0, nch = 0, tLen = m_pText.size();
	bool bp, bn;
	osgText::String wtch = m_pText;

	for (int i = 0; i < tLen; i++)
	{
		bp = bn = true;
		//if ((i - 1 >= 0) && ((wtch[i - 1] < 0x6f0 && wtch[i - 1]>0x600) || (wtch[i - 1] < 0x76E && wtch[i - 1]>0x6f9)))
		//	pch = wtch[i - 1];
		//else
		//	pch = 32;

		//if ((i + 1 < tLen) && ((wtch[i + 1] < 0x6f0 && wtch[i + 1]>0x600) || (wtch[i + 1] < 0x76E && wtch[i + 1]>0x6f9)))

		//if ((i - 1 >= 0 )&& (wtch[i - 1] < 0x76E && wtch[i - 1]>0x600))
			if ((i - 1 >= 0) && ((wtch[i - 1] < 0x660 && wtch[i - 1]>0x600) || (wtch[i - 1] < 0x76E && wtch[i - 1]>0x669)))
			pch = wtch[i - 1];
		else
			pch = 32;

		//if ((i + 1 < tLen) && (wtch[i + 1] < 0x76E && wtch[i + 1]>0x600))
			 if ((i + 1 < tLen) && ((wtch[i + 1] < 0x660 && wtch[i + 1]>0x600) || (wtch[i + 1] < 0x76E && wtch[i + 1]>0x669)))
			nch = wtch[i + 1];
		else
			nch = 32;

		if (pch == 32 || pch == 0x627 || pch == 0x648 || pch == 0x698)  // alef - vav  -zh
			bp = false;
		else if (pch > 0x62E && pch < 0x633)
			bp = false;
		else if (pch > 0x620 && pch < 0x626)
			bp = false;

		if (nch == 32)
			bn = false;

		// start farsi script
		//cout << " text is  =" << std::hex << (int)m_pText[i];
		//cout << "i=" << i << "   t=" << std::hex << m_pText[i] << "pch="<< std::hex << pch<<"   p=" << bp << "    n=" << bn;
		switch (m_pText[i])
		{
			// Hamze
		case 0x626:
			m_pText[i] = CalcChar(0xFE8C, bp, bn);
			break;

			// Alef
		case 0x627://1575
			//cout << " its A ";
			if (bp)
				m_pText[i] = 0xFE8E;//65166
			else
				m_pText[i] = 0xFE8D;
			break;

			// Be
		case 0x628:
			m_pText[i] = CalcChar(0xFE92, bp, bn);//65170
			//cout << "\t  pass1=" << std::hex << (int)m_pText[i];
			break;

			// Te
		case 1578:
			m_pText[i] = CalcChar(65176, bp, bn);
			break;

			// Se
		case 1579:
			m_pText[i] = CalcChar(65180, bp, bn);
			break;

			// Jim
		case 1580:
			m_pText[i] = CalcChar(65184, bp, bn);
			break;

			// He jimi
		case 1581:
			m_pText[i] = CalcChar(65188, bp, bn);
			break;

			// Khe
		case 1582:
			m_pText[i] = CalcChar(65192, bp, bn);
			break;

			// Dal
		case 1583:
			if (bp)
				m_pText[i] = 65194;
			else
				m_pText[i] = 65193;
			break;

			// Zal
		case 1584:
			if (bp)
				m_pText[i] = 65196;
			else
				m_pText[i] = 65195;
			break;

			// Re
		case 1585:
			if (bp)
				m_pText[i] = 65198;
			else
				m_pText[i] = 65197;
			break;

			// Ze
		case 1586:
			if (bp)
				m_pText[i] = 65200;
			else
				m_pText[i] = 65199;
			break;

			// Sin
		case 1587:
			m_pText[i] = CalcChar(65204, bp, bn);
			break;

			// Shin
		case 1588:
			m_pText[i] = CalcChar(65208, bp, bn);
			break;

			// Sad
		case 1589:
			m_pText[i] = CalcChar(65212, bp, bn);
			break;

			// Zad
		case 1590:
			m_pText[i] = CalcChar(65216, bp, bn);
			break;

			// Ta daste dar
		case 1591:
			if (bp)
				m_pText[i] = 65220;
			else
				m_pText[i] = 65219;
			break;

			// Za daste dar
		case 1592:
			if (bp)
				m_pText[i] = 65224;
			else
				m_pText[i] = 65223;
			break;

			// Eyn
		case 1593:
			m_pText[i] = CalcChar(65228, bp, bn);
			break;

			// Gheyn
		case 1594:
			m_pText[i] = CalcChar(65232, bp, bn);
			break;

			// Fe
		case 1601:
			m_pText[i] = CalcChar(65236, bp, bn);
			break;

			// Ghaf
		case 1602:
			m_pText[i] = CalcChar(65240, bp, bn);
			break;

			// Lam
		case 1604:
			m_pText[i] = CalcChar(65248, bp, bn);
			break;

			// Mim
		case 1605:
			m_pText[i] = CalcChar(65252, bp, bn);
			break;

			// Noon
		case 1606:
			m_pText[i] = CalcChar(65256, bp, bn);
			break;

			// He
		case 1607:
			m_pText[i] = CalcChar(65260, bp, bn);
			break;

			// Vav
		case 1608:
			if (bp)
				m_pText[i] = 65262;
			else
				m_pText[i] = 65261;
			break;

			// Pe
		case 1662:
			m_pText[i] = CalcChar(64345, bp, bn);
			break;

			// Che
		case 1670:
			m_pText[i] = CalcChar(64381, bp, bn);
			break;

			// Zhe
		case 1688:
			if (bp)
				m_pText[i] = 64395;
			else
				m_pText[i] = 64394;
			break;

			// Ke
		case 1705:
			m_pText[i] = CalcChar(64401, bp, bn);
			break;

			// Gaf
		case 1711:
			m_pText[i] = CalcChar(64405, bp, bn);
			break;

			// Ye
		case 1740:
		case 1610:
			if (bp && bn)
				m_pText[i] = 65268;
			else if (bp)
				m_pText[i] = 65264;
			else if (bn)
				m_pText[i] = 65267;
			else
				m_pText[i] = 65263;
			break;

		}

		//	cout << "\t\t afertr  =" <<std::hex << m_pText[i] << endl;
	}

	//for (int i = 0; i < tLen; i++)
	//	wtch[i] = m_pText[tLen - i - 1];
	//for (int i = 0; i < tLen; i++)
	//	m_pText[i] = wtch[i];
	return converdirection(m_pText, direction);
	//return m_pText;
	wtch.clear();
}

osgText::String convertutf8::converdirection(osgText::String m_pText, int direction)
{
	int   tLen = m_pText.size();
	int start = 0;
	bool reverse = false;
	osgText::String wtch(m_pText);

	//cout << "direction is :" << direction <<"     terxt=" << m_pText[0] << endl;
	if(m_pText.size()>1)
	if (direction == 1)
	{
		if (!((m_pText[0]>0x600 && m_pText[0] < 0x660) || (m_pText[0]>0x669 && m_pText[0] < 0x76E) || (m_pText[0] <= 0xFEFF && m_pText[0] >= 0xFB50))) {
			reverse = true;
			start = 0;
			//cout << " A[0]     terxt=" << m_pText[0] ;
		}
		for (int i = 1; i < tLen; i++)
		{
			if (m_pText[i] != 32)
				if (!((m_pText[0]>0x600 && m_pText[0] < 0x660) || (m_pText[0]>0x669 && m_pText[0] < 0x76E) || (m_pText[i] <= 0xFEFF && m_pText[i] >= 0xFB50)))
				{
				//	cout << "  p1  ="<< m_pText[i];
					if (!reverse)
					{
						//cout << "    p2=" << m_pText[i];
						reverse = true;
						start = i;
					}
				}
				else {
					//cout << "\tE1 i=" << i;
					if (reverse)
					{
						//cout << "\tE2 i=" << i;
						reverse = false;
						for (int j = start; j < i; j++)
						{
							m_pText[j] = wtch[i - 1 - j + start];
						}
					}
				}
		}
		if (reverse) {
			//	cout << "  fff  ";
			reverse = false;
			int i = tLen - 1;
			for (int j = start; j <= i; j++)
			{
				m_pText[j] = wtch[i - j + start];
			}
		}
	}
	else
	{
		if (((m_pText[0]>0x600 && m_pText[0] < 0x660) || (m_pText[0]>0x669 && m_pText[0] < 0x76E) || (m_pText[0] <= 0xFEFF && m_pText[0] >= 0xFB50))) {
			reverse = true;
			start = 0;

			//cout << "\t P2 i=" << m_pText[0];
		}
		for (int i = 1; i < tLen; i++)
		{
			//cout << "\t P3 i=" << i;
			if (m_pText[i] != 32)
			 if (((m_pText[0]>0x600 && m_pText[0] < 0x660) || (m_pText[0]>0x669 && m_pText[0] < 0x76E) || (m_pText[i] <= 0xFEFF && m_pText[i] >= 0xFB50)))
			{
				//cout << "\t P4 i=" << i;
				if (!reverse)
				{
				//	cout << "\t P5 i=" << i;
					reverse = true;
					start = i;
				}
			}
			else {
				//cout << "\t P6 i=" << i;
				if (reverse)
				{
				//	cout << "\t P7 i=" << i << "    p7j=" << start;
					reverse = false;
					for (int j = start; j < i; j++)
					{
						
						m_pText[j] = wtch[i - 1 - j + start];
					}
				}
			}
		}
		if (reverse) {
			//	cout << "  fff  ";
			reverse = false;
			int i = tLen - 1;
		//	cout << "     End rev" << start << "    to:" << i;
			for (int j = start; j <= i; j++)
			{
				m_pText[j] = wtch[i - j + start];
			}
		}
	}
	return m_pText;
	wtch.clear();
	cout << endl;
}

convertutf8::convertutf8()
{
}


convertutf8::~convertutf8()
{
}
