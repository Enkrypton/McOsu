//================ Copyright (c) 2016, PG, All rights reserved. =================//
//
// Purpose:		hud element drawing functions (accuracy, combo, score, etc.)
//
// $NoKeywords: $osuhud
//===============================================================================//

#ifndef OSUHUD_H
#define OSUHUD_H

#include "OsuScreen.h"

class Osu;
class McFont;
class ConVar;
class Image;

class OsuHUD : public OsuScreen
{
public:
	OsuHUD(Osu *osu);
	virtual ~OsuHUD();

	void draw(Graphics *g);
	void drawDummy(Graphics *g);
	void update();

	void drawCursor(Graphics *g, Vector2 pos, float alphaMultiplier = 1.0f);
	void drawFps(Graphics *g) {drawFps(g, m_tempFont, m_fCurFps);}
	void drawPlayfieldBorder(Graphics *g, Vector2 playfieldCenter, Vector2 playfieldSize, float hitcircleDiameter);
	void drawLoadingSmall(Graphics *g);
	void drawBeatmapImportSpinner(Graphics *g);
	void drawVolumeChange(Graphics *g);
	void drawScoreNumber(Graphics *g, int number, float scale = 1.0f, bool drawLeadingZeroes = false, int offset = 2);
	void drawWarningArrow(Graphics *g, Vector2 pos, bool flipVertically, bool originLeft = true);

	void animateCombo();
	void addHitError(long delta, bool miss = false, bool misaim = false);
	void addTarget(float delta, float angle);

	void animateVolumeChange();

	void animateCursorExpand();
	void animateCursorShrink();

	Rect getSkipClickRect();

private:
	void drawCursorRaw(Graphics *g, Vector2 pos, float alphaMultiplier = 1.0f);
	void drawCursorTrailRaw(Graphics *g, float alpha, Vector2 pos);
	void drawFps(Graphics *g, McFont *font, float fps);
	void drawAccuracy(Graphics *g, float accuracy);
	void drawCombo(Graphics *g, int combo);

	void drawSkip(Graphics *g);
	void drawWarningArrows(Graphics *g, float hitcircleDiameter = 0.0f);
	void drawContinue(Graphics *g, Vector2 cursor, float hitcircleDiameter = 0.0f);
	void drawHitErrorBar(Graphics *g, float hitWindow300, float hitWindow100, float hitWindow50);
	void drawProgressBar(Graphics *g, float percent, bool waiting);
	void drawStatistics(Graphics *g, int bpm, float ar, float cs, float od, int nps, int nd, int ur);
	void drawTargetHeatmap(Graphics *g, float hitcircleDiameter);

	void drawStatisticText(Graphics *g, const UString text);

	Osu *m_osu;
	McFont *m_tempFont;

	ConVar *m_host_timescale_ref;
	ConVar *m_osu_volume_master_ref;
	ConVar *m_osu_mod_target_300_percent_ref;
	ConVar *m_osu_mod_target_100_percent_ref;
	ConVar *m_osu_mod_target_50_percent_ref;

	float m_fAccuracyXOffset;
	float m_fAccuracyYOffset;

	float m_fComboAnim1;
	float m_fComboAnim2;

	// fps counter
	float m_fCurFps;
	int m_iFpsAvgIndex;
	float *m_fpsAvg;
	float m_fFpsUpdate;
	float m_fFpsFontHeight;

	// hit error bar
	struct HITERROR
	{
		float time;
		long delta;
		bool miss;
		bool misaim;
	};
	std::vector<HITERROR> m_hiterrors;

	// volume
	float m_fLastVolume;
	float m_fVolumeChangeTime;
	float m_fVolumeChangeFade;

	// cursor
	float m_fCursorExpandAnim;
	struct CURSORTRAIL
	{
		Vector2 pos;
		float time;
	};
	std::vector<CURSORTRAIL> m_cursorTrail;

	// target heatmap
	struct TARGET
	{
		float time;
		float delta;
		float angle;
	};
	std::vector<TARGET> m_targets;
};

#endif
