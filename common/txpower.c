/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:

	Abstract:

	Revision History:
	Who 		When			What
	--------	----------		----------------------------------------------
*/

#include "rt_config.h"


INT tx_temp_dbg = 0;

#define MDSM_NORMAL_TX_POWER							0x00
#define MDSM_DROP_TX_POWER_BY_6dBm						0x01
#define MDSM_DROP_TX_POWER_BY_12dBm					0x02
#define MDSM_ADD_TX_POWER_BY_6dBm						0x03
#define MDSM_BBP_R1_STATIC_TX_POWER_CONTROL_MASK		0x03




VOID AsicGetTxPowerOffset(struct rtmp_adapter *pAd, ULONG *TxPwr)
{
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC;
	DBGPRINT(RT_DEBUG_INFO, ("-->AsicGetTxPowerOffset\n"));

	memset(&CfgOfTxPwrCtrlOverMAC, 0, sizeof(CfgOfTxPwrCtrlOverMAC));

	CfgOfTxPwrCtrlOverMAC.NumOfEntries = 5; /* MAC 0x1314, 0x1318, 0x131C, 0x1320 and 1324 */

	if (pAd->CommonCfg.BBPCurrentBW == BW_80 &&
		pAd->CommonCfg.Channel > 14)
	{
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx80MPwrCfgABand[0];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx80MPwrCfgABand[1];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx80MPwrCfgABand[2];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx80MPwrCfgABand[3];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx80MPwrCfgABand[4];
	}
	else
	if (pAd->CommonCfg.BBPCurrentBW == BW_40)
	{
		if (pAd->CommonCfg.CentralChannel > 14)
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgABand[4];
		}
		else
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgGBand[4];
		}
	}
	else
	{
		if (pAd->CommonCfg.CentralChannel > 14)
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgABand[4];
		}
		else
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgGBand[4];
		}
	}

	memcpy(TxPwr, (UCHAR *)&CfgOfTxPwrCtrlOverMAC, sizeof(CfgOfTxPwrCtrlOverMAC));

	DBGPRINT(RT_DEBUG_INFO, ("<--AsicGetTxPowerOffset\n"));
}

VOID AsicExtraPowerOverMAC(struct rtmp_adapter *pAd)
{
	uint32_t txpwr = 0;
	uint32_t txpwr7 = 0, txpwr8 = 0, txpwr9 = 0;

	/* For OFDM_54 and HT_MCS_7, extra fill the corresponding register value into MAC 0x13D4 */
	txpwr = mt7612u_read32(pAd, 0x1318);
	txpwr7 |= (txpwr & 0x0000FF00) >> 8; /* Get Tx power for OFDM 54 */
	txpwr = mt7612u_read32(pAd, 0x131C);
	txpwr7 |= (txpwr & 0x0000FF00) << 8; /* Get Tx power for HT MCS 7 */
	mt7612u_write32(pAd, TX_PWR_CFG_7, txpwr7);

	/* For STBC_MCS_7, extra fill the corresponding register value into MAC 0x13DC */
	txpwr = mt7612u_read32(pAd, 0x1324);
	txpwr9 |= (txpwr & 0x0000FF00) >> 8; /* Get Tx power for STBC MCS 7 */
	mt7612u_write32(pAd, TX_PWR_CFG_9, txpwr9);

	if (pAd->CommonCfg.TxStream == 2)
	{
		/* For HT_MCS_15, extra fill the corresponding register value into MAC 0x13DC */
		txpwr = mt7612u_read32(pAd, 0x1320);
		txpwr8 |= (txpwr & 0x0000FF00) >> 8; /* Get Tx power for HT MCS 15 */
		mt7612u_write32(pAd, TX_PWR_CFG_8, txpwr8);
	}

}


/*
	==========================================================================
	Description:
		Gives CCK TX rate 2 more dB TX power.
		This routine works only in LINK UP in INFRASTRUCTURE mode.

		calculate desired Tx power in RF R3.Tx0~5,	should consider -
		0. if current radio is a noisy environment (pAd->DrsCounters.fNoisyEnvironment)
		1. TxPowerPercentage
		2. auto calibration based on TSSI feedback
		3. extra 2 db for CCK
		4. -10 db upon very-short distance (AvgRSSI >= -40db) to AP

	NOTE: Since this routine requires the value of (pAd->DrsCounters.fNoisyEnvironment),
		it should be called AFTER MlmeDynamicTxRatSwitching()
	==========================================================================
 */
VOID AsicAdjustTxPower(struct rtmp_adapter *pAd)
{
	INT i, j;
	CHAR Value;
	CHAR Rssi = -127;
	CHAR DeltaPwr = 0;
	CHAR TxAgcCompensate = 0;
	CHAR DeltaPowerByBbpR1 = 0;
	CHAR TotalDeltaPower = 0; /* (non-positive number) including the transmit power controlled by the MAC and the BBP R1 */
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC = {0};

#ifdef CONFIG_STA_SUPPORT
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;

	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE) ||
		RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS))
		return;

	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if(INFRA_ON(pAd))
		{
			Rssi = RTMPMaxRssi(pAd,
						   pAd->StaCfg.RssiSample.AvgRssi0,
						   pAd->StaCfg.RssiSample.AvgRssi1,
						   pAd->StaCfg.RssiSample.AvgRssi2);
		}
	}
#endif /* CONFIG_STA_SUPPORT */

	/* Get Tx rate offset table which from EEPROM 0xDEh ~ 0xEFh */
	RTMP_CHIP_ASIC_TX_POWER_OFFSET_GET(pAd, (PULONG)&CfgOfTxPwrCtrlOverMAC);
	/* Get temperature compensation delta power value */

	DBGPRINT(RT_DEBUG_INFO, ("%s(): DeltaPwr=%d, TotalDeltaPower=%d, TxAgcCompensate=%d, DeltaPowerByBbpR1=%d\n",
			__FUNCTION__,
			DeltaPwr,
			TotalDeltaPower,
			TxAgcCompensate,
			DeltaPowerByBbpR1));



	/* Get delta power based on the percentage specified from UI */
	AsicPercentageDeltaPower(pAd, Rssi, &DeltaPwr,&DeltaPowerByBbpR1);

	/* The transmit power controlled by the BBP */
	TotalDeltaPower += DeltaPowerByBbpR1;
	/* The transmit power controlled by the MAC */
	TotalDeltaPower += DeltaPwr;

	{
		AsicCompensatePowerViaBBP(pAd, &TotalDeltaPower);
	}
}

VOID AsicPercentageDeltaPower(
	IN 		struct rtmp_adapter *		pAd,
	IN		CHAR				Rssi,
	INOUT	PCHAR				pDeltaPwr,
	INOUT	PCHAR				pDeltaPowerByBbpR1)
{
	/*
		Calculate delta power based on the percentage specified from UI.
		E2PROM setting is calibrated for maximum TX power (i.e. 100%).
		We lower TX power here according to the percentage specified from UI.
	*/

	if (pAd->CommonCfg.TxPowerPercentage >= 100) /* AUTO TX POWER control */
	{
#ifdef CONFIG_STA_SUPPORT
		if ((pAd->OpMode == OPMODE_STA)
		)
		{
			/* To patch high power issue with some APs, like Belkin N1.*/
			if (Rssi > -35)
			{
				*pDeltaPwr -= 12;
			}
			else if (Rssi > -40)
			{
				*pDeltaPwr -= 6;
			}
			else
				;
		}
#endif /* CONFIG_STA_SUPPORT */
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 90) /* 91 ~ 100% & AUTO, treat as 100% in terms of mW */
		;
	else if (pAd->CommonCfg.TxPowerPercentage > 60) /* 61 ~ 90%, treat as 75% in terms of mW		 DeltaPwr -= 1; */
	{
		*pDeltaPwr -= 1;
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 30) /* 31 ~ 60%, treat as 50% in terms of mW		 DeltaPwr -= 3; */
	{
		*pDeltaPwr -= 3;
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 15) /* 16 ~ 30%, treat as 25% in terms of mW		 DeltaPwr -= 6; */
	{
		*pDeltaPowerByBbpR1 -= 6; /* -6 dBm */
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 9) /* 10 ~ 15%, treat as 12.5% in terms of mW		 DeltaPwr -= 9; */
	{
		*pDeltaPowerByBbpR1 -= 6; /* -6 dBm */
		*pDeltaPwr -= 3;
	}
	else /* 0 ~ 9 %, treat as MIN(~3%) in terms of mW		 DeltaPwr -= 12; */
	{
		*pDeltaPowerByBbpR1 -= 12; /* -12 dBm */
	}
}


VOID AsicCompensatePowerViaBBP(struct rtmp_adapter *pAd, CHAR *pTotalDeltaPower)
{
	UCHAR mdsm_drop_pwr;

	if (IS_MT7601(pAd) || IS_MT76x2(pAd))
	{
		return;
	}

	DBGPRINT(RT_DEBUG_INFO, ("%s: <Before> TotalDeltaPower = %d dBm\n", __FUNCTION__, *pTotalDeltaPower));

	if (*pTotalDeltaPower <= -12)
	{
		*pTotalDeltaPower += 12;
		mdsm_drop_pwr = MDSM_DROP_TX_POWER_BY_12dBm;
	}
	else if ((*pTotalDeltaPower <= -6) && (*pTotalDeltaPower > -12))
	{
		*pTotalDeltaPower += 6;
		mdsm_drop_pwr = MDSM_DROP_TX_POWER_BY_6dBm;
	}
	else
	{
		/* Control the the transmit power by using the MAC only */
		mdsm_drop_pwr = MDSM_NORMAL_TX_POWER;
	}

	DBGPRINT(RT_DEBUG_INFO, ("%s: Drop the BBP transmit power by %d dBm!\n",
				__FUNCTION__,
				(mdsm_drop_pwr == MDSM_DROP_TX_POWER_BY_12dBm ? 12 : \
				(mdsm_drop_pwr == MDSM_DROP_TX_POWER_BY_6dBm ? 6 : 0))));

	if (IS_RT65XX(pAd))
	{
		uint32_t bbp_val = 0;

		bbp_val = RTMP_BBP_IO_READ32(pAd, TXBE_R4);
		bbp_val &= (~0x3);
		bbp_val |= mdsm_drop_pwr;
		RTMP_BBP_IO_WRITE32(pAd, TXBE_R4, bbp_val);
		DBGPRINT(RT_DEBUG_INFO, ("%s: <After> TotalDeltaPower = %d dBm, TXBE_R4 = 0x%0x\n", __FUNCTION__, *pTotalDeltaPower, bbp_val));
	}

}

/*
	========================================================================

	Routine Description:
		Read initial channel power parameters from EEPROM

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:

	========================================================================
*/
VOID RTMPReadChannelPwr(struct rtmp_adapter *pAd)
{
	uint32_t 				i, choffset;

	/* Read Tx power value for all channels*/
	/* Value from 1 - 0x7f. Default value is 24.*/
	/* Power value : 2.4G 0x00 (0) ~ 0x1F (31)*/
	/*             : 5.5G 0xF9 (-7) ~ 0x0F (15)*/

	/* 0. 11b/g, ch1 - ch 14*/
	for (i = 0; i < 7; i++)
	{
#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) || defined(RT5592) || defined(RT3290)
		if (IS_RT65XX(pAd))
		{
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;

			if ((Power.field.Byte0 > 0x27) || (Power.field.Byte0 < 0))
			{
				pAd->TxPower[i * 2].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2].Power = Power.field.Byte0;
			}

			if ((Power.field.Byte1 > 0x27) || (Power.field.Byte1 < 0))
			{
				pAd->TxPower[i * 2 + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Power = Power.field.Byte1;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPower[%d].Power = 0x%02X, TxPower[%d].Power = 0x%02X\n",
				__FUNCTION__,
				i * 2,
				pAd->TxPower[i * 2].Power,
				i * 2 + 1,
				pAd->TxPower[i * 2 + 1].Power));

		}
		else
#endif /* defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) || defined(RT5592) */
		{ /* Default routine. RT3070 and RT3370 run here. */
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;
		}
	}


	{
		/* 1. U-NII lower/middle band: 36, 38, 40; 44, 46, 48; 52, 54, 56; 60, 62, 64 (including central frequency in BW 40MHz)*/
		/* 1.1 Fill up channel*/
		choffset = 14;
		for (i = 0; i < 4; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 36 + i * 8 + 0;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 36 + i * 8 + 2;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 36 + i * 8 + 4;
		}

		/* 1.2 Fill up power*/

		/* 2. HipperLAN 2 100, 102 ,104; 108, 110, 112; 116, 118, 120; 124, 126, 128; 132, 134, 136; 140 (including central frequency in BW 40MHz)*/
		/* 2.1 Fill up channel*/
		choffset = 14 + 12;
		for (i = 0; i < 5; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 100 + i * 8 + 0;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 100 + i * 8 + 2;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 100 + i * 8 + 4;
		}
		pAd->TxPower[3 * 5 + choffset + 0].Channel		= 140;


		/* 3. U-NII upper band: 149, 151, 153; 157, 159, 161; 165, 167, 169; 171, 173 (including central frequency in BW 40MHz)*/
		/* 3.1 Fill up channel*/
		choffset = 14 + 12 + 16;
		/*for (i = 0; i < 2; i++)*/
		for (i = 0; i < 3; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 149 + i * 8 + 0;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 149 + i * 8 + 2;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 149 + i * 8 + 4;
		}
		pAd->TxPower[3 * 3 + choffset + 0].Channel		= 171;

		pAd->TxPower[3 * 3 + choffset + 1].Channel		= 173;

		/* 3.2 Fill up power*/
		/*for (i = 0; i < 4; i++)*/
	}


	/* 4. Print and Debug*/
	/*choffset = 14 + 12 + 16 + 7;*/
	choffset = 14 + 12 + 16 + 11;


}

