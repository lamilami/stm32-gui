#include "chinese_pinyin.h"

//ºº×ÖÅÅÁĞ±í
const unsigned char PY_mb_space     []={""};
const unsigned char PY_mb_a     []={"°¡°¢ß¹ï¹àÄëç"};
const unsigned char PY_mb_ai    []={"°®°£°¤°¥°¦°§°¨°©°ª°«°¬°­°¯ŞßàÈàÉæÈè¨êÓíÁïÍö°"};
const unsigned char PY_mb_an    []={"°²°³°´°µ°¶°¸°°°±ÚÏ°·ÛûŞîáíâÖèñï§ğÆ÷ö"};
const unsigned char PY_mb_ang   []={"°º°»°¹óa"};
const unsigned char PY_mb_ao    []={"°¼°½°¾°¿°À°Á°Â°Ã°ÄÛêŞÖà»òüöË÷¡÷éá®âÚåÛæÁæñéáñú"};
const unsigned char PY_mb_ba    []={"°Ë°Í°Ö°Î°Å°Æ°Ç°È°É°Ê°Ì°Ï°Ğ°Ñ°Ò°Ó°Ô°ÕÜØİÃá±å±îÙôÎöÑ÷É"};
const unsigned char PY_mb_bai   []={"°×°Ø°Ù°Ú°Û°Ü°İ°Ş²®Şãêş"};
const unsigned char PY_mb_ban   []={"°ë°ì°ß°à°á°â°ã°ä°å°æ°ç°è°é°ê°íÚæÛàêÚîÓñ£ñ­ô²"};
const unsigned char PY_mb_bang  []={"°î°ï°ğ°ñ°ò°ó°ô°õ°ö°÷°ø°ùİòäº"};
const unsigned char PY_mb_bao   []={"°ü±¦±£±§±¨±©°ú°û°ı°ş±¡±¢±¤±¥±ª±«±¬ÅÙÅÚÙèİáæßìÒğ±ñÙõÀöµ"};
const unsigned char PY_mb_bei   []={"±³±´±±±¶±­±®±¯±°±²±µ±·±¸±¹±º±»±ÛØÃÚéÚıÛıİÉİíßÂã£íÕğÇñØöÍ÷¹"};;
const unsigned char PY_mb_ben   []={"±¾±¿±¼±½ÛÎÛĞêÚï¼"};
const unsigned char PY_mb_beng  []={"°ö±À±Á±Â±Ã±Ä±ÅÜ¡àÔê´"};
const unsigned char PY_mb_bi    []={"±Æ±Ç±È±É±Ê±Ë±Ì±Í±Î±Ï±Ğ±Ñ±Ò±Ó±Ô±ÕØ°±Ö±×±Ø±Ù±Ú±Û±Ü±İÃØÃÚÙÂÛıÜÅÜêİ©İÉŞµßÁßÙáùâØã¹ääå¨åöåşæ¾æÔèµêÚî¯îéïõñÔóÙóëó÷ô°ôÅõÏ÷Â"};
const unsigned char PY_mb_bian  []={"±ß±à±á±ã±ä±å±Ş±â±æ±ç±è±éØÒÛÍÜĞâíãêçÂìÔí¾íÜñ¹ñÛòùóÖöı"};
const unsigned char PY_mb_biao  []={"±í±ê±ë±ìæ»æôè¼ì©ì­ì®ïÚïğñ¦ñÑ÷§÷Ô"};
const unsigned char PY_mb_bie   []={"±ğ±î±ï±ñõ¿"};
const unsigned char PY_mb_bin   []={"±ò±ó±ô±õ±ö±÷ÙÏáÙçÍçãéÄéëë÷ïÙ÷Æ÷Ş"};
const unsigned char PY_mb_bing  []={"±ø±ù±ú±û±ü±ı±ş²¡²¢ÆÁÙ÷ÙûÚûŞğéÄ"};
const unsigned char PY_mb_bo    []={"°Ø°Ù°ş±¡²©²£²¤²·²¥²¦²§²¨²ª²«²¬²­²®²¯²°²±²²²³²´²µØÃÙñŞ¬à£âÄéŞë¢íçîàğ¾ô¤õÀõËõÛ"};
const unsigned char PY_mb_bu    []={"²»²¼²½±¤²¶²·²¸²¹²º²¾²¿²ÀÆÒß²åÍê³êÎîĞîßõ³"};
const unsigned char PY_mb_ca    []={"²Áàêíå"};
const unsigned char PY_mb_cai   []={"²Å²Æ²Ç²Â²Ã²Ä²È²É²Ê²Ë²Ì"};
const unsigned char PY_mb_can   []={"²Í²Î²Ï²Ğ²Ñ²Ò²Óåîæîè²ôÓ÷õ"};
const unsigned char PY_mb_cang  []={"²Ô²Õ²Ö²×²ØØ÷"};
const unsigned char PY_mb_cao   []={"²İ²Ù²Ú²Û²ÜÜ³àĞäîó©ô½"};
const unsigned char PY_mb_ce    []={"²à²á²â²Ş²ßâü"};
const unsigned char PY_mb_cen   []={" ²Îá¯ä¹"};
const unsigned char PY_mb_ceng  []={"²ã²äÔøàá"};
const unsigned char PY_mb_cha   []={"²å²æ²ç²è²é²ê²ë²ì²í²î²ïÉ²ÔûñÃàêâªâÇãâæ±è¾é«é¶éßïÊïï"};
const unsigned char PY_mb_chai  []={"²î²ğ²ñ²òÙ­îÎğûò²ö·"};
const unsigned char PY_mb_chan  []={"²ú²û²ü²ó²ô²õ²ö²÷²ø²ùåîµ¥ÙæÚÆİÛâÜâãäıå¤åñæ¿êèìøïâó¸õğ"};
const unsigned char PY_mb_chang []={"³¤³§²ı²ş³¡³¢³£³¥³¦³¨³©³ª³«ØöÛËÜÉİÅáäâêã®ãÑæ½æÏêÆë©öğ"};
const unsigned char PY_mb_chao  []={"³¬³­³®³¯³°³±³²³³³´´Â½Ëâ÷êËñé"};
const unsigned char PY_mb_che   []={"³µ³¶³·³¸³¹³ºÛååøíº"};
const unsigned char PY_mb_chen  []={"³»³¼³½³¾³¿³À³Á³Â³Ã³Ä³ÆÚÈÚßŞÓàÁå·è¡é´í×ö³"};
const unsigned char PY_mb_cheng []={"³Å³Æ³Ç³È³É³Ê³Ë³Ì³Í³Î³Ï³Ğ³Ñ³Ò³ÓÊ¢Ø©ÛôàááçèÇèßëóîªîñîõñÎòÉõ¨"};
const unsigned char PY_mb_chi   []={"³Ô³Õ³Ö³×³Ø³Ù³Ú³Û³Ü³İ³Ş³ß³à³á³â³ãó×ß³ßêÙÑÛæÜ¯Üİà´àÍáÜâÁæÊë·í÷ğ·ñ¡ñİò¿ó¤óøôùõØ÷Î"};
const unsigned char PY_mb_chong []={"³ä³å³æ³ç³èÖÖÖØÜûâçã¿ï¥ô©ô¾öÅ"};
const unsigned char PY_mb_chou  []={"³é³ê³ó³ë³ì³í³î³ï³ğ³ñ³ò³ôÙ±àüã°ñ¬öÅ"};
const unsigned char PY_mb_chu   []={"³ö³õ³÷³ø³ù³ú³û³ü³ı³ş´¡´¢´£´¤´¥´¦ĞóØ¡Û»âğãÀç©èÆèúéËñÒòÜõé÷í"};
const unsigned char PY_mb_chuai []={"´§ŞõàÜëúõß"};
const unsigned char PY_mb_chuan []={"´¨´©´ª´«´¬´­´®â¶å×çİë°îËô­"};
const unsigned char PY_mb_chuang[]={"´¯´°´±´²´³´´âëğÚ"};
const unsigned char PY_mb_chui  []={"´µ´¶´·´¸´¹Úïé¢é³"};
const unsigned char PY_mb_chun  []={"´º´»´¼´½´¾´¿´Àİ»ğÈòí"};
const unsigned char PY_mb_chuo  []={"´Á´Âà¨åÁê¡õÖöº"};
const unsigned char PY_mb_ci    []={"´Ë´Ì´Í´ÎËÅ²î´Ã´Ä´Å´Æ´Ç´È´É´Ê×ÈÜëßÚìôğËôÒôÙ"};
const unsigned char PY_mb_cong  []={"´Ó´Ô´Ï´Ğ´Ñ´ÒÜÊäÈæõçıè®èÈ"};
const unsigned char PY_mb_cou   []={"´Õé¨ê£ëí"};
const unsigned char PY_mb_cu    []={"´Ö´×´Ø´ÙİıáŞâ§éãõ¡õ¾õí"};
const unsigned char PY_mb_cuan  []={"´Ú´Û´ÜÔÜÙàß¥ìàïé"};
const unsigned char PY_mb_cui   []={"´İ´Ş´ß´à´á´â´ã´äİÍßıã²è­éÁë¥ö¿"};
const unsigned char PY_mb_cun   []={"´å´æ´çââñå"};
const unsigned char PY_mb_cuo   []={"´è´é´ê´ë´ì´íØÈáÏëâï±ïóğîğûõºõãõò"};
const unsigned char PY_mb_da    []={"´ó´î´ï´ğ´ñ´òŞÇßÕàªâòæ§í³ğãñ×óÎ÷°÷²"};
const unsigned char PY_mb_dai   []={"´ó´ô´õ´ö´÷´ø´ù´ú´û´ü´ı´şµ¡÷ìÜ¤ß°ß¾á·åÊææçªçé"};
const unsigned char PY_mb_dan   []={"µ¢µ£µ¤µ¥µ¦µ§µ¨µ©µªµ«µ¬µ­µ®µ¯µ°ÉÄÊ¯ÙÙİÌà¢å£ééêæíñğãğ÷ñõóì"};
const unsigned char PY_mb_dang  []={"µ±µ²µ³µ´µµÚÔÛÊİĞå´í¸îõñÉ"};
const unsigned char PY_mb_dao   []={"µ¶µ·µ¸µ¹µºµ»µ¼µ½µ¾µ¿µÀµÁØÖß¶àüâáë®ìâôî"};
const unsigned char PY_mb_de    []={"µÂµÃµÄµØï½"};
const unsigned char PY_mb_dei   []={"µÃ"};
const unsigned char PY_mb_deng  []={"³ÎµÅµÆµÇµÈµÉµÊµËàâáØê­íãïëô£"};
const unsigned char PY_mb_di    []={"µÄµÖµ×µØµÙµÚµÛµÜµİµÌµÍµÎµÏµĞµÑµÒµÓµÔµÕµŞÌáØµÙáÚ®ÚĞÛ¡Ûæİ¶àÖæ·èÜé¦êëíÆíÚíûïáôÆ÷¾"};
const unsigned char PY_mb_dia   []={"àÇ"};
const unsigned char PY_mb_dian  []={"µçµêµëµãµäµåµìµíµîµßµàµáµâµæµèµéÚçÛãáÛçèîäñ°ñ²ô¡õÚ"};
const unsigned char PY_mb_diao  []={"µõµóµôµöµ÷µïµğµñµòîöï¢õõöô"};
const unsigned char PY_mb_die   []={"µøµùµúµûµüµıµşÛìÜ¦Şéà©ëºğ¬ñóõŞöø"};
const unsigned char PY_mb_ding  []={"¶¡¶¢¶£¶¤¶¥¶¦¶§¶¨¶©Øêà¤çàëëíÖî®îúğÛñôôú"};
const unsigned char PY_mb_diu   []={"¶ªîû"};
const unsigned char PY_mb_dong  []={"¶«¶¬¶­¶®¶¯¶°¶±¶²¶³¶´ßËá´á¼ë±ëËëØíÏğ´"};
const unsigned char PY_mb_dou   []={"¶¹¶º¶»¶¼¶µ¶¶¶·¶¸İúñ¼ò½óû"};
const unsigned char PY_mb_du    []={"¶Ç¶È¶É¶¼¶½¶¾¶¿¶À¶Á¶Â¶Ã¶Ä¶Å¶Æ¶ÊÜ¶à½äÂèüë¹ó¼óÆ÷Ç÷ò"};
const unsigned char PY_mb_duan  []={"¶Ë¶Ì¶Í¶Î¶Ï¶Ğé²ìÑóı"};
const unsigned char PY_mb_dui   []={"¶Ñ¶Ò¶Ó¶Ôí¡í­íÔ"};
const unsigned char PY_mb_dun   []={"¶Ü¶Õ¶Ö¶×¶Ø¶Ù¶Ú¶Û¶İãçìÀí»íâíïïæõ»"};
const unsigned char PY_mb_duo   []={"¶à¶ä¶È¶Ş¶ß¶á¶â¶ã¶å¶æ¶ç¶è¶éÍÔßÍßáãõç¶îìñÖõâ"};
const unsigned char PY_mb_e     []={"°¢¶ê¶ë¶ì¶í¶î¶ï¶ğ¶ñ¶ò¶ó¶ô¶õ¶öÅ¶Ø¬ÚÌÛÑÜÃİ­İàßÀãµåíæ¹éîëñï°ïÉğÊò¦öù"};
const unsigned char PY_mb_ei    []={"ÚÀ"};
const unsigned char PY_mb_en    []={"¶÷İìŞô"};
const unsigned char PY_mb_er    []={"¶ş¶ø¶ù¶ú¶û¶ü¶ı·¡åÇçíîïğ¹öÜ"};
const unsigned char PY_mb_fa    []={"·¢·£·¤·¥·¦·§·¨·©ÛÒíÀ"};
const unsigned char PY_mb_fan   []={"·²·³·´·µ·¶···¸·¹·º·ª·«·¬·­·®·¯·°·±Ş¬ŞÀá¦èóìÜî²õì"};
const unsigned char PY_mb_fang  []={"·»·¼·½·¾·¿·À·Á·Â·Ã·Ä·ÅØÎÚúèÊîÕô³öĞ"};
const unsigned char PY_mb_fei   []={"·Æ·Ç·È·É·Ê·Ë·Ì·Í·Î·Ï·Ğ·ÑÜÀáôì³ã­åúç³äÇé¼êÚëèìéíÉïĞğòòãóõôäö­öî"};
const unsigned char PY_mb_fen   []={"·Ö·Ò·Ü·İ·Ş·ß·à·Ó·Ô·Õ·×·Ø·Ù·Ú·ÛÙÇå¯çãèûêÚö÷÷÷"};
const unsigned char PY_mb_feng  []={"·á·â·ã·ä·å·æ·ç·ï·è·é·ê·ë·ì·í·îÙºÛºİ×ßôããí¿"};
const unsigned char PY_mb_fo    []={"·ğ"};
const unsigned char PY_mb_fou   []={"·ñó¾"};
const unsigned char PY_mb_fu    []={"¸´·ğ¸µ¸¶¸·¸¸·ò·ó·ô·õ¸¾·ö·÷·ø·ù·ú·û·ü·ı·ş¸¡¸¢¸£¸¤¸¥¸¦¸§¸¨¸©¸ª¸«¸¬¸­¸®¸¯¸°¸±¸²¸³¸¹¸º¸»¸¼¸½¸¿¸ÀÙëÙìÚâÛ®Ü½ÜÀÜŞÜòİ³İÊŞÔß»á¥âöäæåõæÚæâç¦ç¨èõêçìğíÉíêíëî·ïûğ¥ò¶òİòğòóôïõÃõÆöÖöû"};
const unsigned char PY_mb_ga    []={"¸Á¸Â¼Ğ¿§Ù¤ŞÎæØæÙê¸îÅ"};
const unsigned char PY_mb_gai   []={"¸Ã¸Ä¸Å¸Æ¸Ç¸È½æØ¤ÚëÛòê®êàëÜ"};
const unsigned char PY_mb_gan   []={"¸É¸Ê¸Ë¸Ì¸Í¸Î¸Ï¸Ğ¸Ñ¸Ò¸ÓÛáÜÕŞÏß¦ãïäÆä÷ç¤éÏêºí·ğáôû"};
const unsigned char PY_mb_gang  []={"¸Ô¸Õ¸Ö¸×¸Ø¸Ù¸Ú¸Û¸Ü¿¸í°î¸óà"};
const unsigned char PY_mb_gao   []={"¸æ¸Ş¸ß¸à¸İ¸á¸â¸ã¸ä¸åØºÚ¾Û¬Ş»çÉéÀéÂê½ï¯"};
const unsigned char PY_mb_ge    []={"¸ö¸÷¸Ç¸ç÷Àëõ¸è¸é¸ê¸ë¸ì¸í¸î¸ï¸ğ¸ñ¸ò¸ó¸ô¸õºÏ¿©ØªØîÛÁÛÙÜªàÃæüë¡îşïÓñËò´ô´"};
const unsigned char PY_mb_gei   []={"¸ø"};
const unsigned char PY_mb_gen   []={"¸ù¸úØ¨İ¢ßçôŞ"};
const unsigned char PY_mb_geng  []={"¸û¸ü¸ı¸ş¹¡¹¢¹£¾±ßìâÙç®öá"};
const unsigned char PY_mb_gong  []={"¹¤¹²¹¥¹¦¹§¹«¹¬¹­¹¨¹©¹ª¹®¹¯¹°¹±ò¼ŞÃçîëÅö¡"};
const unsigned char PY_mb_gou   []={"¹³¹´¹µ¹¶¹»¹¸¹¹¹ºØşÚ¸¹·óôá¸åÜæÅçÃèÛêíì°óÑ÷¸"};
const unsigned char PY_mb_gu    []={"¹¼¹½¹¾¹¿¹À¹Á¹Â¹Ã¹Ä¹Å¹Æ¹Ç¹È¹É¹Ê¹Ë¹Ì¹Í¼ÖØÅÚ¬İÔáÄãéèôéïêôêöëûì±î­î¹îÜïÀğ³ğÀğóòÁôşõıöñ÷½"};
const unsigned char PY_mb_gua   []={"¹Î¹Ï¹Ğ¹Ñ¹Ò¹ÓØÔÚ´ßÉèéëÒğ»"};
const unsigned char PY_mb_guai  []={"¹Ô¹Õ¹ÖŞâ"};
const unsigned char PY_mb_guan  []={"¹Ø¹Ù¹Ú¹Û¹Ü¹İ¹Ş¹ß¹à¹áÂÚÙÄİ¸¹×ŞèäÊîÂğÙ÷¤"};
const unsigned char PY_mb_guang []={"¹â¹ã¹äßÛáîèæë×"};
const unsigned char PY_mb_gui   []={"¹å¹æ¹ç¹è¹é¹ê¹ë¹ì¹í¹î¹ğ¹ñ¹ò¹ó¹ô¹ïÈ²ØĞØÛâÑå³æ£èíêÁêĞğ§óşöÙ÷¬"};
const unsigned char PY_mb_gun   []={"¹õ¹ö¹÷ÙòçµíŞöç"};
const unsigned char PY_mb_guo   []={"¹ø¹ù¹ú¹û¹ü¹ıÎĞÙåÛöŞâßÃàşáÆâ£é¤ë½ï¾ñøòäòå"};
const unsigned char PY_mb_ha    []={"¹ş¸òîş"};
const unsigned char PY_mb_hai   []={"»¹¿Èº¢º£º¦º¤º¥º§º¡àËëÜõ°"};
const unsigned char PY_mb_han   []={"º¹ººº°º®º¬º­º¯º±º¨ºµº¶º·º¸º©ºªº«º²º³÷ıº´ÚõİÕŞşå«êÏìÊñüò¥òÀ"};
const unsigned char PY_mb_hang  []={"ĞĞº»º¼º½¿ÔÏïãìç¬ñş"};
const unsigned char PY_mb_hao   []={"ºÂºÃºÄºÅê»ğ©ºÁºÆå°¸äº¾º¿ºÀºÑİïŞ¶àÆàãå©ò«òº"};
const unsigned char PY_mb_he    []={"ºÇºÈºÉºÊºËºÌºÍºÎºÏºÓºĞºÑºÒºÔºÕºØºÖº×ÏÅÚ­ÛÀÛÖàÀãØæüêÂîÁò¢òÂôç"};
const unsigned char PY_mb_hei   []={"ºÚºÙ"};
const unsigned char PY_mb_hen   []={"ºÛºÜºİºŞ"};
const unsigned char PY_mb_heng  []={"ºßºàºáºâºãŞ¿çñèì"};
const unsigned char PY_mb_hong  []={"ºìºäºåºæºçºèºéºêºëÙäÙêÚ§İ¦Ş®Ş°ãÈãü"};
const unsigned char PY_mb_hou   []={"ºóºíºîºïºğºñºòÜ©ááåËğúóóô×ö×÷¿"};
const unsigned char PY_mb_hu    []={"»¤»¥»¦»§ºËºôºõºöº÷ºøºùºúºû»¢ºüºıºş»¡»£Ùüßüàñá²â©âïã±ä°äïçúéÎéõì²ìÃìÎìæìèìïğ­ğÀğÉğ×ò®óËõ­õú÷½"};
const unsigned char PY_mb_hua   []={"»¨»ª»«»¬»©»­»®»¯»°æèèëí¹îü"};
const unsigned char PY_mb_huai  []={"»µ»±»²»³»´õ×"};
const unsigned char PY_mb_huan  []={"»¶»·»¸»¹»º»»»¼»½»¾»À»Á»Â»Ã÷ßä½»¿Û¨Û¼ÛùİÈß§à÷âµä¡äñå¾åÕçÙïÌöé"};
const unsigned char PY_mb_huang []={"»Î»Ä»Å»Æ»Ç»È»É»Ê»Ë»Ì»Í»Ï»Ğ»ÑÚòáåäÒäêåØè«ëÁñ¥ó¨óòöü"};
const unsigned char PY_mb_hui   []={"»á»Ø»Ù»Ú»Ò»Ó»Ô»Õ»Ö»×»Û»Ü»İ»Ş»ß»à»â»ã»ä»å»æåçÀ£Ú¶ÜîÜöŞ¥ßÔßÜà¹ãÄä§ä«çÀèíêÍí£ò³ó³÷â"};
const unsigned char PY_mb_hun   []={"»ç»è»é»ê»ë»ìÚ»âÆãÔäãçõ"};
const unsigned char PY_mb_huo   []={"ºÍ»í»î»ï»ğ»ñ»ò»ó»ô»õ»öØåŞ½ß«àëâ·îØïÁïìñëó¶"};
const unsigned char PY_mb_ji    []={"¼Æ¼Ç¸ø¼¼»÷»ù¼¸¼¹¼º»ø¼®¼¯¼°¼±¼²¼³¼´¼µ¼¶¼·¼»¼È¼É¼Ê¼½¼¾¼¿¼À¼Á»ú»û»ü»ı¼¡¼¢¼£¼¤¼¥¼¦¼§¼¨¼©¼ª¼«¼¬»ş¼­¼Â¼Ã¼Ä¼Å¼Ë¼Ì¼Í½åÆæÏµØ¢Ø½ØÀØŞÙ¥ÙÊÛÔÜ¸ÜÁÜùİ½İğŞªŞáß´ßÒßâßóá§áÕä©åæåìæ÷çÜçáé®éêêªê«êåêéê÷ì´í¶î¿ïúğ¢ñ¤ò±óÅóÇôßõÒõÕö«öİöê÷Ù÷ä"};
const unsigned char PY_mb_jia   []={"¼Ò¼Ó¼Î¼Ğ¼Ñ¼Ô¼Õ¼Ö¼×¼Ø¼Ù¼Ú¼Û¼Ü¼İ¼Ş¼ÏÇÑØÅÙ¤Û£İçáµä¤åÈçìê©ëÎí¢îòîşïØğèğıñÊòÌóÕôÂõÊ"};
const unsigned char PY_mb_jian  []={"½¨¼û¼ş¼ò½¡¼õ¼ß¼ö¼à¼ñ¼ó¼ô¼á¼â¼ä¼å¼æ¼ç¼è¼é¼ê¼ë¼ì¼í¼î¼ï¼ğ¼ã¼÷¼ø¼ù¼ú¼ü¼ı½¢½£½¤½¥½¦½§ÙÔÚÉÚÙÚÚİÑİóŞöàîäÕå¿åÀçÌèÅé¥ê§ê¯êğêùë¦ëìíúïµğÏñĞóÈôåõÂõİöä÷µ"};
const unsigned char PY_mb_jiang []={"½²ºç½©½ª½«½¬½­½®½¯½°½±½³½´½µÇ¿Üüä®ç­çÖêñíäñğôİôø"};
const unsigned char PY_mb_jiao  []={"½Ğ½Ï¾õ½ÇĞ£½¶½·½¸½¹½º½»½¼½½½¾½¿½À½Á½Â½Ã½Ä½Å½Æ½È½É½Ê½Ë½Ì½Í½Î½ÑÙ®ÙÕÜ´ÜúŞØàİá½áèæ¯ë¸ğ¨ğÔòÔõ´õÓöŞ"};
const unsigned char PY_mb_jie   []={"½à½á½â½ã½ä½Ò½Ü½Ó½Ô½ç½è½é½İ½Ş½Õ½Ö½×½Ø½Ù½Ú½Û½ß½å½æ½ê½ë½ìÙÊÚ¦ÚµÚàŞ×à®àµæ¼æİèîíÙïÇğÜò¡ò»ôÉöÚ÷º"};
const unsigned char PY_mb_jin   []={"½í¾¡½î½ï½ğ½ñ½ò½ô½õ½ö½÷½ø½ù½ú½û½ü½ı½ş¾¢½óÚáİ£İÀàäâËâÛæ¡çÆèªéÈêáêîîÄñÆñæ"};
const unsigned char PY_mb_jing  []={"¾©¾ª¾«¾­¾®¾¦¾§¾°¾»¾±¾²¾³¾´¾¯¾µ¾¶¾¹¾º¾¢¾£¾¤¾¥¾¨¾¬¾·¾¸ØÙÙÓÚåÚêİ¼â°ã½ãşåÉåòæºëÂëÖëæìºö¦"};
const unsigned char PY_mb_jiong []={"¾¼¾½ØçåÄìç"};
const unsigned char PY_mb_jiu   []={"¾Å¾Í¾È¾¾¾¿¾À¾Á¾Â¾Ã¾Ä¾Æ¾É¾Ê¾Ë¾Ì¾Î¾ÇÙÖà±ãÎèÑèêğ¯ğÕôñ÷İ"};
const unsigned char PY_mb_ju    []={"¾Ş¾ß¾à¾ã¾ä¾å³µ¹ñ¾ç¾Ó¾Ô¾Õ¾Ö¾×¾Ø¾Ù¾Ú¾Û¾Ü¾İ¾á¾â¾æ¾Ï¾Ğ¾Ñ¾ÒÙÆÚªÜÄÜÚÜìŞäåáåğè¢èÛé§é°é·éÙêøì«îÒï¸ñÀñÕôòõ¶õáö´öÂöÄ÷¶"};
const unsigned char PY_mb_juan  []={"¾ì¾í¾è¾é¾ê¾ë¾îÈ¦Û²áúä¸èğîÃïÃïÔöÁ"};
const unsigned char PY_mb_jue   []={"¾ö¾÷¾ø¾õ½Ç¾ò¾ó½À½Å¾ï¾ğ¾ñ¾ôØÊØãÚÜÛÇÜ¥Ş§àÙáÈâ±æŞçåèöéÓìßïãõêõû"};
const unsigned char PY_mb_jun   []={"¾ü¾ı¾ù¾ú¾û¾ş¿¡¿¢¿£¿¤¿¥¹êŞÜñäóŞ÷å"};
const unsigned char PY_mb_ka    []={"¿¨¿¦¿§¿©ØûßÇëÌ"};
const unsigned char PY_mb_kai   []={"¿ª¿«¿¬¿­¿®ØÜÛîİÜâéâıîøï´ïÇ"};
const unsigned char PY_mb_kan   []={"¿´¿¯¿°¿±¿²¿³Ù©íèî«ÛÉİ¨ãÛ¼÷ê¬"};
const unsigned char PY_mb_kang  []={"¿µ¿¶¿·¿¸¿¹¿º¿»ØøãÊîÖ"};
const unsigned char PY_mb_kao   []={"¿¼¿¿¿½¿¾èàêûîíåê"};
const unsigned char PY_mb_ke    []={"¿É¿Ê¿Ë¿Æ¿Ì¿Í¿Îà¾¿À¿Á¿Â¿Ã¿Ä¿Å¿Ç¿Èã¡òòá³äÛïıæìç¼çæéğë´î§îİîşºÇï¾ğâñ½ò¤òÂ÷Á"};
const unsigned char PY_mb_ken   []={"¿Ï¿Ğ¿Ñ¿ÒñÌ"};
const unsigned char PY_mb_keng  []={"¿Ó¿Ôï¬ëÖîï"};
const unsigned char PY_mb_kong  []={"¿Õ¿Ö¿×¿ØÙÅáÇóí"};
const unsigned char PY_mb_kou   []={"¿Ù¿Ú¿Û¿ÜÜÒŞ¢ßµíîóØ"};
const unsigned char PY_mb_ku    []={"¿İ¿Ş¿ß¿à¿á¿â¿ãç«÷¼ØÚÜ¥à·"};
const unsigned char PY_mb_kua   []={"¿ä¿å¿æ¿ç¿èÙ¨ï¾"};
const unsigned char PY_mb_kuai  []={"»á¿é¿ê¿ë¿ìØáÛ¦ßàáöëÚ"};
const unsigned char PY_mb_kuan  []={"¿í¿î÷Å"};
const unsigned char PY_mb_kuang []={"¿ö¿ï¿ğ¿ñ¿ò¿ó¿ô¿õÚ²Ú¿Ú÷ÛÛŞÅßÑæşêÜ"};
const unsigned char PY_mb_kui   []={"¿÷¿ø¿ù¿ú¿û¿ü¿ı¿şÀ¡À¢À£Ø¸ØÑåÓî¥õÍÙçÚóİŞŞñà­à°ã¦ã´êÒñùòñóñ"};
const unsigned char PY_mb_kun   []={"À¤À¥À¦À§ã§çûï¿õ«öïãÍ÷Õ"};
const unsigned char PY_mb_kuo   []={"À¨À©ÀªÀ«òÒ"};
const unsigned char PY_mb_la    []={"À¬À­À®À¯À°À±À²ÂäØİååê¹íÇğø"};
const unsigned char PY_mb_lai   []={"À³À´ÀµáÁáâäµäşêãíùñ®ô¥ïª"};
const unsigned char PY_mb_lan   []={"À¶À·À¸À¹ÀºÀ»À¼À½À¾À¿ÀÀÀÁÀÂÀÃÀÄá°äíé­ìµïçñÜî½"};
const unsigned char PY_mb_lang  []={"ÀÉÀÊÀËÀÅÀÆÀÇÀÈà¥ãÏòëï¶İõïüİ¹"};
const unsigned char PY_mb_lao   []={"ÀÌÀÍÀÎÀÏÀĞÀÑÀÒÀÓÀÔÂäÂçßëáÀõ²èáîîï©ğìñì"};
const unsigned char PY_mb_le    []={"ÀÕÀÖÁËØìß·ãî÷¦"};
const unsigned char PY_mb_lei   []={"ÀÛÀÕÀ×ÀØÀÙÀÚÀÜÀİÀŞÀßÀàÀáÙúÚ³àÏæĞçĞéÛñçõª"};
const unsigned char PY_mb_leng  []={"ÀâÀãÀäÜ¨ã¶"};
const unsigned char PY_mb_li    []={"ÀûÁ¦ÀúÀ÷Á¢Á£ÀñÁ¤ÀôÀíÀîÀïÀåÀøÀöÀæÀçÁ¥ÀèÀéÀëÀìÀğÀõÀùÀòÀóÀêÀüÀıÀşÁ¡Á§Á¨ØªÙ³ÙµÛªÛŞÜÂİ°İñŞ¼ß¿à¦à¬áûäàå¢åÎæ²æËæêçÊèÀèİéöìåíÂíÇîºî¾ï®ğ¿ğİğßòÃòÛó»óÒóöôÏõ·õÈö¨öâ÷¯÷ó"};
const unsigned char PY_mb_lia   []={"Á©"};
const unsigned char PY_mb_lian  []={"ÁªÁ«Á¬Á®Á¯Á°Á±Á²Á³Á´ÁµÁ¶Á·äòÁ­å¥çöé¬ŞÆéçİüì¡ñÍñÏó¹öã"};
const unsigned char PY_mb_liang []={"Á½ÁÁÁ©Á¸Á¹ÁºÁ»Á¼Á¾Á¿ÁÀÁÂÜ®İ¹é£õÔ÷Ë"};
const unsigned char PY_mb_liao  []={"ÁËÁÃÁÏÁÄÁÅÁÆÁÇÁÈÁÉÁÊÁÌÁÍÁÎŞ¤ŞÍàÚâ²å¼çÔîÉğÓ"};
const unsigned char PY_mb_lie   []={"ÁĞÁÑÁÒÁÓä£ÁÔÙıÛøŞæßÖôóõñ÷à"};
const unsigned char PY_mb_lin   []={"ÁÙÁÚÁŞÁàÁÕÁÖÁ×ÁØÁÛÁÜÁİÁßİşßøá×âŞãÁåàéİê¥ì¢î¬ôÔõï÷ë"};
const unsigned char PY_mb_ling  []={"ÁîÁéÁíÀâÁáÁâÁãÁäÁåÁæÁçÁèÁêÁëñöÁìÛ¹ÜßßÊàòãöç±èÚèùê²òÈôáöì"};
const unsigned char PY_mb_liu   []={"ÁùÁïÁğÁñÁòÁóÁôÁõÁöÁ÷ÁøÂµÂ½ä¯åŞæòç¸ì¼ìÖï³ïÖğÒöÌ"};
const unsigned char PY_mb_lo    []={"¿©"}; 
const unsigned char PY_mb_long  []={"ÁúÅªÁûÁüÁıÁşÂ¡Â¢Â£Â¤ÛâÜ×ãñççèĞëÊíÃñª"};
const unsigned char PY_mb_lou   []={"Â¥Â¦Â§Â¨Â©ÂªÂ¶ÙÍİäà¶áĞïÎğüñïò÷÷Ã"};
const unsigned char PY_mb_lu    []={"ÁùÂ«Â¬Â­Â®Â¯Â°Â±Â²Â³Â´ÂµÂ¶Â·Â¸Â¹ÂºÂ»Â¼Â½Â¾ÂÌÛäß£ààãòäËäõåÖè´èÓéÖéñéûê¤êÚëªëÍïåğµğØóüôµöÔ"};
const unsigned char PY_mb_lv    []={"ÂËÂÊÂÌÂÀÂÁÂÂÂÃÂÄÂÅÂÆÂÇÂÈÂÉÂ¿ñÚÙÍŞÛãÌéµëöïù"}; 
const unsigned char PY_mb_luan  []={"ÂÒÂÏÂÍÂÎÂĞÂÑ"};
const unsigned char PY_mb_lue   []={"ÂÓÂÔï²"};
const unsigned char PY_mb_lun   []={"ÂØÂÕÂÖÂ×ÂÙÂÚÂÛàğ"};
const unsigned char PY_mb_luo   []={"ÂäÂŞ¸õ¿©ÀÓÂÜÂİÂßÂàÂáÂâÂãÂåÂæÂçÙÀÙùÜıŞÛŞûâ¤ãøäğçóé¡ëáíÑïİñ§öÃ"};
const unsigned char PY_mb_m     []={"ß¼"};  
const unsigned char PY_mb_ma    []={"ÂèÂéÂêÂëÂìÂíÂîÂïÂğÄ¦Ä¨ßéáïæÖè¿ó¡"};
const unsigned char PY_mb_mai   []={"ÂñÂ÷ÂøÂùÂúÂûÂüÂıÂşÃ¡Ü¬á£çÏì×ïÜò©òı÷©÷´"};
const unsigned char PY_mb_man   []={"ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
const unsigned char PY_mb_mang  []={"Ã¢Ã£Ã¤Ã¥Ã¦Ã§ÚøäİíËòş"};
const unsigned char PY_mb_mao   []={"Ã¨Ã©ÃªÃ«Ã¬÷ÖÃ®Ã¯Ã°Ã±Ã²Ã³ÙóÃ­Üâá¹ã÷è£êÄêóë£ì¸í®î¦òúó±"};
const unsigned char PY_mb_me    []={"Ã´"};
const unsigned char PY_mb_mei   []={"Ã¿ÃÃÃÀÃµÃ¶ÃÁÃÂñÇ÷ÈÃ·Ã¸Ã¹ÃºÃ»Ã¼Ã½Ã¾ÃÄİ®áÒâ­ä¼äØé¹ïÑğÌ"};
const unsigned char PY_mb_men   []={"ÃÅÃÆÃÇŞÑìËí¯îÍ"};
const unsigned char PY_mb_meng  []={"ÃÈÃÎÃÉÃÊÃËÃÌÃÍÃÏÛÂİùŞ«ãÂëüíæòµòìó·ô»ô¿"};
const unsigned char PY_mb_mi    []={"ÃĞÃÑÃÒÃÓÃÔÃÕÃÖÃ×ÃØÃÙÃÚÃÛÃÜ÷çÚ×ÃİØÂÚ¢ŞÂßäà×â¨ãèåµåôæùëßìòôÍôé÷ã"};
const unsigned char PY_mb_mian  []={"ÃæÃŞÃßÃàÃáÃâÃãÃäÃåãæäÅäÏå²ëïíí"};
const unsigned char PY_mb_miao  []={"ÃçÃèÃéÃêÃëÃìÃíÃîß÷åãç¿çÑèÂíµíğğÅ"};
const unsigned char PY_mb_mie   []={"ÃïÃğØ¿ßãóúóº"};
const unsigned char PY_mb_min   []={"ÃñÃòÃóÃôÃõÃöÜåáºãÉãıçÅçäçëíªö¼÷ª"};
const unsigned char PY_mb_ming  []={"Ã÷ÃøÃùÃúÃûÃüÚ¤ÜøäéêÔî¨õ¤"};
const unsigned char PY_mb_miu   []={"ÃıçÑ"};
const unsigned char PY_mb_mo    []={"ÂöÃ»ÃşÄ¡Ä¢Ä£Ä¤Ä¥Ä¦Ä§Ä¨Ä©ÄªÄ«Ä¬Ä­Ä®Ä¯Ä°÷áÍòÚÓÜÔİëâÉæÆéâïÒï÷ñ¢ñòõöõø"};
const unsigned char PY_mb_mou   []={"Ä±Ä²Ä³Ù°ßèçÑíøòÖöÊ"};
const unsigned char PY_mb_mu    []={"Ä¾Ä¿ÄÀÄ£Ä²Ä´ÄµÄ¶Ä·Ä¸Ä¹ÄºÄ»Ä¼Ä½ÄÁÄÂÜÙãåØïÛéë¤îâ"};
const unsigned char PY_mb_na    []={"ÄÃÄÄÄÅÄÆÄÇÄÈÄÉŞàëÇïÕñÄ"};
const unsigned char PY_mb_nai   []={"ÄÊÄËÄÌÄÍÄÎØ¾Ù¦ÜµİÁèÍ"};
const unsigned char PY_mb_nan   []={"ÄÏÄĞÄÑà«àïéªëîòïôö"};
const unsigned char PY_mb_nang  []={"ÄÒàìâÎß­êÙ"};
const unsigned char PY_mb_nao   []={"ÄÓÄÔÄÕÄÖÄ×Ø«ÛñßÎâ®è§íĞîóòÍ"};
const unsigned char PY_mb_ne    []={"ÄÄÄØÚ«"};
const unsigned char PY_mb_nei   []={"ÄÚÄÙ"};
const unsigned char PY_mb_nen   []={"ÄÛí¥"};
const unsigned char PY_mb_neng  []={"ÄÜ"};
const unsigned char PY_mb_ng    []={"àÅ"}; 
const unsigned char PY_mb_ni    []={"ÄØÄİÄŞÄßÄàÄáÄâÄãÄäÄåÄæÄçÙ£Ûèâ¥âõêÇì»ìòí«íşîêöò"};
const unsigned char PY_mb_nian  []={"ÄèÄéÄêÄëÄìÄíÄîØ¥Ûşéığ¤öÓöó"};
const unsigned char PY_mb_niang []={"ÄïÄğ"};
const unsigned char PY_mb_niao  []={"ÄñÄòëåôÁÜàæÕ"};
const unsigned char PY_mb_nie   []={"ÄóÄôÄõÄöÄ÷ÄøÄùõæŞÁà¿Ø¿Úíò¨ô«"};
const unsigned char PY_mb_nin   []={"Äú"};
const unsigned char PY_mb_ning  []={"ÄûÄüÄıÄşÅ¡Å¢ØúßÌå¸ñ÷"};
const unsigned char PY_mb_niu   []={"Å£Å¤Å¥Å¦ŞÖæ¤áğâî"};
const unsigned char PY_mb_nong  []={"Å§Å¨Å©ÅªÙ¯ßæ"};
const unsigned char PY_mb_nou   []={"ññ"};
const unsigned char PY_mb_nu    []={"Å«Å¬Å­åóæÀæÛæå"};
const unsigned char PY_mb_nuan  []={"Å¯"};
const unsigned char PY_mb_nue   []={"Å±Å°"};
const unsigned char PY_mb_nuo   []={"ÄÈÅ²Å³Å´ÅµÙĞŞùßöï»"};
const unsigned char PY_mb_nv    []={"Å®í¤îÏô¬"};
const unsigned char PY_mb_o     []={"Å¶à¸àŞ"};
const unsigned char PY_mb_ou    []={"Å·Å¸Å¹ÅºÅ»Å¼Å½ÇøÚ©âæê±ñî"};
const unsigned char PY_mb_pa    []={"°Ç°ÒÅ¾Å¿ÅÀÅÁÅÂÅÃİâèËóá"};
const unsigned char PY_mb_pai   []={"ÅÄÅÅÅÆÅÇÅÈÅÉÆÈÙ½İåßß"};
const unsigned char PY_mb_pan   []={"·¬ÅÊÅËÅÌÅÍÅÎÅÏÅĞÅÑó´õçÅÖŞÕãÜãİãúêÚñÈñá"};
const unsigned char PY_mb_pang  []={"°ò°õ°÷ÅÒÅÓÅÔÅÕÅÖáİäèó¦åÌ"};
const unsigned char PY_mb_pao   []={"Å×ÅØÅÙÅÚÅÛÅÜÅİáóâÒğåëãŞË"};
const unsigned char PY_mb_pei   []={"ÅŞÅßÅàÅáÅâÅãÅäÅåÅæàÎö¬àúì·ïÂõ¬"};
const unsigned char PY_mb_pen   []={"ÅçÅèäÔ"};
const unsigned char PY_mb_peng  []={"ÅõÅöÅéÅêÅëÅìÅíÅîÅïÅğÅñÅòÅóÅôâñÜ¡àØó²"};
const unsigned char PY_mb_pi    []={"±Ù·ñÅ÷ÅøÅùÅúÅûÅüÅıÅşÆ¡Æ¢Æ£Æ¤Æ¥Æ¦Æ§Ø§Æ¨Æ©ñ±õùØòÚéÚğÚüÛ¯ÛÜÛıÜ±ÜÅß¨àèâÏäÄæÇç¢èÁê¶î¢î¼îëñÔñâò·òç"};
const unsigned char PY_mb_pian  []={"±â±ãÆªÆ«Æ¬Æ­ÚÒæéçÂêúëİôæõä"};
const unsigned char PY_mb_piao  []={"Æ®Æ¯Æ°Æ±ÆÓØâæÎçÎî©àÑæôéèóª"};
const unsigned char PY_mb_pie   []={"Æ²Æ³Ø¯ÜÖë­"};
const unsigned char PY_mb_pin   []={"Æ´ÆµÆ¶Æ·Æ¸æ°æÉé¯êòò­"};
const unsigned char PY_mb_ping  []={"·ëÆ¹ÆºÆ»Æ¼Æ½Æ¾Æ¿ÆÀÆÁÙ·æ³èÒöÒ"};
const unsigned char PY_mb_po    []={"²´·±ÆÂÆÃÆÄÆÅÆÆÆÇÆÈÆÉÆÓØÏÚéÛ¶çêê·ë¶îÇîŞğ«óÍ"};
const unsigned char PY_mb_pou   []={"ÆÊÙöŞå"};
const unsigned char PY_mb_pu    []={"ÆÕ±¤±©¸¬ÆËÆÌÆÍÆÎÆÏÆĞÆÑÆÒÆÓÆÔÆÖÆ×ÆØÆÙÙéàÛäßõëå§è±ë«ïäïè"};
const unsigned char PY_mb_qi    []={"»ü¼©ÆÚÆÛÆÜÆİÆŞÆßÆàÆáÆâÆãÆäÆåÆæÆçÆèÆéÆêÆëÆìÆíáªÆîÆïÆğÆñÆòÆóÆôç÷çùè½ÆõÆöÆ÷ÆøÆùÆúÆûÆüÆıØ½ì÷í¬õè÷¢÷èØÁÙ¹ÛßÜ»ÜÎÜùİÂİİä¿æëç²êÈŞ­èçéÊì¥àÒá¨ãàíÓñıòÓòàôëôì"};
const unsigned char PY_mb_qia   []={"¿¨ÆşÇ¡Ç¢İÖñÊ÷Ä"};
const unsigned char PY_mb_qian  []={"Ç£Ç¤Ç¥Ç¦Ç§Ç¨Ç©ÇªÇ«Ç¬Ç­Ç®Ç¯Ç°Ç±Ç²Ç³Ç´ÇµÇ¶Ç·Ç¸ÏËÙ»ÙİÚäÜ·ÜÍÜçİ¡Şçá©ã¥ã»å¹åºå½ç×èıêùëÉí©îÔò¯óéôÇ"};
const unsigned char PY_mb_qiang []={"Ç¹ÇºÇ»Ç¼Ç½Ç¾Ç¿ÇÀõÄãŞê¨ìÁïÏïêãÜñßæÍéÉòŞôÇ"};
const unsigned char PY_mb_qiao  []={"¿ÇÇÁÇÂÇÃÇÄÇÅÇÆÇÇÇÈÇÉÇÊÇËÇÌÇÍÇÎÇÏÈ¸Ú½ÚÛÜñá½ã¾éÔõÎ÷³çØØäã¸íÍï¢"};
const unsigned char PY_mb_qie   []={"ÇĞÇÑÇÒÇÓÇÔÙ¤ã«ã»æªôòÛ§êüïÆóæ"};
const unsigned char PY_mb_qin   []={"ÇÕÇÖÇ×ÇØÇÙÇÚÇÛÇÜÇİÇŞÇßÜËŞìôÀßÄàºàßâÛéÕï·ñæñûòû"};
const unsigned char PY_mb_qing  []={"Ç×ÇàÇáÇâÇãÇäÇåÇæÇçÇèÇéÇêÇëÇìíàÜÜàõéÑïºòßóÀóäôìö¥öë÷ô"};
const unsigned char PY_mb_qiong []={"ÇíÇîñ·òËÚöÜäóÌõ¼öÆ"};
const unsigned char PY_mb_qiu   []={"³ğ¹êÇïÇğÇñÇòÇóÇôÇõÇöÙ´åÏôÃôÜåÙÛÏáìäĞé±êäò°òÇòøöú"};
const unsigned char PY_mb_qu    []={"Ç÷ÇøÇùÇúÇûÇüÇıÇşÈ¡È¢È£È¤È¥òĞ÷ñĞçÚ°Û¾ÛÉÜÄŞ¡Ş¾á«áéãÖè³êïë¬ëÔìîíáğ¶ñ³ó½ôğöÄ"};
const unsigned char PY_mb_quan  []={"È¦È§È¨È©ÈªÈ«È¬È­È®È¯È°Ú¹Üõòé÷Üáëãªç¹éúî°îıóÜ"};
const unsigned char PY_mb_que   []={"È±È²È³È´ÈµÈ¶È·È¸ã×ãÚí¨"};
const unsigned char PY_mb_qun   []={"È¹ÈºåÒ÷å"};
const unsigned char PY_mb_ran   []={"È»È¼È½È¾ÜÛòÅ÷×"};
const unsigned char PY_mb_rang  []={"È¿ÈÀÈÁÈÂÈÃìüğ¦"};
const unsigned char PY_mb_rao   []={"ÈÄÈÅÈÆÜéæ¬èã"};
const unsigned char PY_mb_re    []={"ÈÇÈÈßö"};
const unsigned char PY_mb_ren   []={"ÈÉÈÊÈËÈÌÈÍÈÎÈÏÈĞÈÑÈÒïşØéØğÜóİØâ¿éíñÅ"};
const unsigned char PY_mb_reng  []={"ÈÓÈÔ"};
const unsigned char PY_mb_ri    []={"ÈÕ"};
const unsigned char PY_mb_rong  []={"ÈÖÈ×ÈØÈÙÈÚÈÛÈÜÈİÈŞÈßáÉáõéÅëÀòî"};
const unsigned char PY_mb_rou   []={"ÈàÈáÈâôÛõå÷·"};
const unsigned char PY_mb_ru    []={"ÈãÈäÈåÈæÈçÈèÈéÈêÈëå¦ÈìäáİêàéŞ¸ä²çÈï¨ñàò¬"};
const unsigned char PY_mb_ruan  []={"ÈíÈîëÃ"};
const unsigned char PY_mb_rui   []={"ÈïÈğÈñÜÇî£èÄŞ¨ò¸"};
const unsigned char PY_mb_run   []={"ÈòÈó"};
const unsigned char PY_mb_ruo   []={"ÈôÈõÙ¼óè"};
const unsigned char PY_mb_sa    []={"ÈöÈ÷ÈøØ¦ØíìªëÛ"};
const unsigned char PY_mb_sai   []={"ÈùÈúÈûÈüàç"};
const unsigned char PY_mb_san   []={"ÈıÈşÉ¡É¢âÌë§ôÖ"};
const unsigned char PY_mb_sang  []={"É£É¤É¥Şúíßòª"};
const unsigned char PY_mb_sao   []={"É¦É§É¨É©ëığşÜ£çÒöş"};
const unsigned char PY_mb_se    []={"ÈûÉªÉ«É¬ØÄï¤ğ£"};
const unsigned char PY_mb_sen   []={"É­"};
const unsigned char PY_mb_seng  []={"É®"};
const unsigned char PY_mb_sha   []={"É¯É°É±É²É³É´ÉµÉ¶É·É¼ÏÃğğôÄö®öèßşì¦ï¡"};
const unsigned char PY_mb_shai  []={"É«É¸É¹"};
const unsigned char PY_mb_shan  []={"²ôµ¥ÉºÉ»É¼É½É¾É¿ÉÀÉÁÉÂÉÃÉÄÉÅÉÆÉÇÉÈÉÉÕ¤Ú¨ğŞô®óµõÇ÷­ØßÛ·ÛïÜÏáêäúæ©æÓæóëşìøîÌ÷Ô"};
const unsigned char PY_mb_shang []={"ÉÊÉËÉÌÉÍÉÎÉÏÉĞÉÑç´éäõüÛğìØ"};
const unsigned char PY_mb_shao  []={"ÇÊÉÒÉÓÉÔÉÕÉÖÉ×ÉØÉÙÉÚÉÛÉÜÛ¿Üæô¹äûè¼òÙóâ"};
const unsigned char PY_mb_she   []={"ÉİÉŞÉßÉàÉáÉâÉãÉäÉåÉæÉçÉè÷êÕÛØÇÙÜŞéâ¦äÜì¨î´îè"};
const unsigned char PY_mb_shei  []={"Ë­"}; 
const unsigned char PY_mb_shen  []={"²ÎÉéÉêÉëÉìÉíÉîÉïÉğÉñÉòÉóÉôÉõÉöÉ÷ÉøÊ²Ú·ÚÅİ·İØßÓäÉé©ëÏïòò×"};
const unsigned char PY_mb_sheng []={"³ËÉùÉúÉûÉüÉıÉşÊ¡Ê¢Ê£Ê¤Ê¥óÏáÓäÅêÉíò"};
const unsigned char PY_mb_shi   []={"³×Ê¦Ê§Ê¨Ê©ÊªÊ«Ê¬Ê­Ê®Ê¯Ê°Ê±Ê²Ê³Ê´ÊµÊ¶Ê·Ê¸Ê¹ÊºÊ»Ê¼Ê½Ê¾Ê¿ÊÀÊÁÊÂÊÃÊÄÊÅÊÆÊÇÊÈÊÉÊÊÊËÊÌÊÍÊÎÊÏÊĞÊÑÊÒÊÓÊÔËÆß±óÂÖ³ÖÅÚÖÛõİªİéâ»éøêÛìÂìêîæîèó§óßõ§õ¹öåöõ"};
const unsigned char PY_mb_shou  []={"ÊÕÊÖÊ×ÊØÊÙÊÚÊÛÊÜÊİÊŞŞĞá÷ç·ô¼"};
const unsigned char PY_mb_shu   []={"ÊßÊàÊáÊâÊãÊäÊåÊæÊçÊèÊéÊêÊëÊìÊíÊîÊïÊğÊñÊòÊóÊôÊõÊöÊ÷ÊøÊùÊúÊûÊüÊıÊşË¡Ù¿ÛÓãğäøæ­Ø­İÄŞóç£ë¨ëòì¯ïíïøñâ"};
const unsigned char PY_mb_shua  []={"Ë¢Ë£à§"};
const unsigned char PY_mb_shuai []={"ÂÊË¤Ë¥Ë¦Ë§ó°"};
const unsigned char PY_mb_shuan []={"Ë¨Ë©ãÅäÌ"};
const unsigned char PY_mb_shuang[]={"ËªË«Ë¬ãñæ×"};
const unsigned char PY_mb_shui  []={"Ë®Ë¯Ë°Ëµãß"};
const unsigned char PY_mb_shun  []={"Ë±Ë²Ë³Ë´"};
const unsigned char PY_mb_shuo  []={"ÊıËµË¶Ë·Ë¸İôŞ÷åùéÃîå"};
const unsigned char PY_mb_si    []={"Ë¹ËºË»Ë¼Ë½Ë¾Ë¿ËÀËÁËÂËÃËÄËÅËÆËÇËÈØËßĞÙ¹ÙîÛÌâ»ãáãôäùæ¦æáçÁìëïÈğ¸ñêòÏóÓ"};
const unsigned char PY_mb_song  []={"ËÉËÊËËËÌËÍËÎËÏËĞáÔâìã¤äÁñµáÂİ¿Ú¡"};
const unsigned char PY_mb_sou   []={"ËÑËÒËÓËÔÛÅà²âÈäÑì¬î¤ïËòôàÕŞ´"};
const unsigned char PY_mb_su    []={"ËÕËÖË×ËØËÙËÚËÛËÜËİËŞËßËàËõÙíãºä³óùöÕÚÕİøà¼ö¢"};
const unsigned char PY_mb_suan  []={"ËáËâËãâ¡"};
const unsigned char PY_mb_sui   []={"ËäËêËçËåËæËèËîËìËéËíËë"};
const unsigned char PY_mb_sun   []={"ËïËğËñ"};
const unsigned char PY_mb_suo   []={"ËòËóËôËõËöË÷ËøËùßïàÂàÊæ¶É¯èøêıíüôÈ"};
const unsigned char PY_mb_ta    []={"ËúËûËüËıËşÌ¡Ì¢í³Ì£Ì¤ÍØãËåİé½îèõÁäâ÷£äğ"};
const unsigned char PY_mb_tai   []={"Ì¥Ì¦Ì§Ì¨Ì©ÌªÌ«Ì¬Ì­õÌÛ¢Ş·ææëÄìÆîÑöØ"};
const unsigned char PY_mb_tan   []={"µ¯Ì®Ì¯Ì°Ì±Ì²Ì³Ì´ÌµÌ¶Ì·Ì¸Ì¹ÌºÌ»Ì¼Ì½Ì¾Ì¿ñûÛ°å£ê¼êæìşîãïÄïâ"};
const unsigned char PY_mb_tang  []={"ÌÀÌÁÌÂÌÃÌÄÌÅÌÆÌÇÌÈÌÉÌÊÌËÌÌÙÎâ¼äçè©éÌîõó«ï¦ïÛñíó¥ôÊõ±àû"};
const unsigned char PY_mb_tao   []={"ÌÍÌÎÌÏÌĞÌÑÌÒÌÓÌÔÌÕÌÖÌ×ß¶ßû÷Òä¬èºìâØ»"};
const unsigned char PY_mb_te    []={"ÌØß¯ìıï«"};
const unsigned char PY_mb_teng  []={"ÌÙÌÚÌÛëøÌÜ"};
const unsigned char PY_mb_ti    []={"ÌİÌŞÌßÌàÌáÌâÌãÌäÌåÌæÌçÌèÌéÌêÌëÙÃã©ç¾ÜèåÑç°ğÃñÓõ®"};
const unsigned char PY_mb_tian  []={"ÌìÌíÌîÌïÌğÌñÌòÌóéåŞİãÃãÙî±îäï»"};
const unsigned char PY_mb_tiao  []={"µ÷ÌôÌõÌöÌ÷ÌøÙ¬÷ØÜæìöï¢ñ»òèóÔôĞö¶öæ"};
const unsigned char PY_mb_tie   []={"ÌùÌúÌû÷Ñï°İÆ"};
const unsigned char PY_mb_ting  []={"ÌüÌıÌşÍ¡Í¢Í£Í¤Í¥Í¦Í§ÜğİãæÃîúòÑöªèè"};
const unsigned char PY_mb_tong  []={"Í©Í«Í¬Í­Í®Í¯Í°Í±Í²Í³Í´Ù¡Ù×ÜíâúäüÍªÙÚÛíàÌá¼íÅ"};
const unsigned char PY_mb_tou   []={"ÍµÍ¶Í·Í¸÷»î×Ùï"};
const unsigned char PY_mb_tu    []={"Í¹ÍºÍ»Í¼Í½Í¾Í¿ÍÀÍÁÍÂÍÃÜ¢İ±İËîÊõ©"};
const unsigned char PY_mb_tuan  []={"ÍÄÍÅŞÒåèî¶"};
const unsigned char PY_mb_tui   []={"ÍÆÍÇÍÈÍÉÍÊÍËìÕ"};
const unsigned char PY_mb_tun   []={"¶ÚÍÊÍÌÍÍÍÎâ½ëàÙÛêÕ"};
const unsigned char PY_mb_tuo   []={"ËµÍÏÍØÍĞÍÑÍÒÍÓÍÔÍÕÍÖÍ×ÍÙõÉØ±Ù¢ÛçãûèØèŞéÒíÈîèö¾óêõ¢âÕ"};
const unsigned char PY_mb_wa    []={"ÍÚÍÛÍÜÍİÍŞÍßÍàØôæ´ëğ"};
const unsigned char PY_mb_wai   []={"ÍáÍâáË"};
const unsigned char PY_mb_wan   []={"ÂûÍãÍäÍåÍæÍçÍèÍéÍêÍëÍìÍíÍîÍïÍğÍñÍòÍóØàÜ¹İ¸İÒæıòêçºçşëäîµ÷´"};
const unsigned char PY_mb_wang  []={"ÍôÍõÍöÍ÷ÍøÍùÍúÍûÍüÍıØèã¯÷ÍŞÌéş"};
const unsigned char PY_mb_wei   []={"ÎªÎ»Î½ÍşÎ¡Î¢Î£Î¤Î¬Î¥Î¦Î§Î¨Î©Î«Î­Î®Î¯Î°Î±Î²Î³Î´ÎµÎ¶Î·Î¸Î¹ÎºÎ¼Î¾Î¿ÎÀÙËÚÃÚóÛ×İÚŞ±àøá¡áËáÍâ¬åÔæ¸ğôì¿çâãÇâ«Úñãíä¢ä¶è¸ê¦ìĞôºöÛàí"};
const unsigned char PY_mb_wen   []={"ÎÊÎÄÎÅÎÆÎÁÎÂÎÃÎÇÎÈÎÉØØö©çäãÓãëè·"};
const unsigned char PY_mb_weng  []={"ÎËÎÌÎÍİîŞ³"};
const unsigned char PY_mb_wo    []={"ÎÎÎÏÎĞÎÑÎÒÎÓÎÔÎÕÎÖÙÁİ«à¸á¢ö»ä×ë¿íÒ"};
const unsigned char PY_mb_wu    []={"ÎåÎïÎğÎñÎçÎèÎéÎäÎê¶ñÎòÎóØ£Î×ÎíÎØÎÙÎÚÎÛÎÜÎİÎŞÎßÎàÎáÎâÎãÎæÎëÎìÎîØõÚùğÄÛØÜÌßíâĞâäâèğÍğíòÚä´å»åÃåüæÄæğÚãè»êõì¶ìÉöÈ÷ù"};
const unsigned char PY_mb_xi    []={"Ï£Ï°Ï¦Ï·Ï¸ÎôÎõÎöÎ÷ÎøÎùÎúÎûÎüÎıÎşÏ¡õèÏ¢Ï¤Ï¥Ï§Ï¨ÏªÏ«Ï¬Ï®Ï¯Ï±Ï²Ï´ÏµÏ¶ôËğªåïæÒçôéØŞÉÜçÏ­Ï©Ï³ØÎÙÒÙâÚôÛ­İ¾İßİûßñáãâ¾ãÒä»äÀêØêêì¤ì¨ìäìùìûñ¶ñÓòáó£ó¬ôªô¸ôÑôâõµ÷û"};
const unsigned char PY_mb_xia   []={"Ï¹ÏºÏ»Ï¼Ï½Ï¾Ï¿ÏÀÏÁÏÂÏÃÏÄÏÅßÈáòåÚè¦èÔíÌóÁ÷ï"};
const unsigned char PY_mb_xian  []={"Ï³Ï´ÏÆÏÇÏÈÏÉÏÊÏËÏÌÏÍÏÎÏÏÏĞÏÑÏÒÏÓÏÔÏÕÏÖÏ×ÏØÏÙÏÚÏÛÏÜÏİÏŞÏßÙşÜÈİ²Şºá­áıåßæµë¯ìŞììğÂğçğïò¹óÚôÌõ£õĞõÑö±"};
const unsigned char PY_mb_xiang []={"ÏñÏòÏó½µÏàÏáÏâÏãÏäÏæÏçÏèÏéÏêÏëÏìÏíÏîÏïÏğÏå÷ÏÜ¼İÙâÃâÔæøç½ó­öß"};
const unsigned char PY_mb_xiao  []={"Ğ¡ÏûĞ¤ÏôÏõÏöÏ÷ÏøÏùÏúÏüÏıÏşĞ¢Ğ£Ğ¥Ğ¦Ğ§ßØäìåĞóãóïæçç¯èÉèÕòÙ÷Ì"};
const unsigned char PY_mb_xie   []={"Ğ©ĞªĞ«Ğ¬Ğ­Ğ®Ğ¯Ğ°Ğ±Ğ²Ğ³Ğ´ĞµĞ¶Ğ·Ğ¸Ğ¹ĞºĞ»Ğ¼Ñª½âĞ¨Ò¶ÙÉÙôÛÄÛÆŞ¯ß¢â³âİäÍå¬åâç¥çÓé¿éÇò¡õóöÙ÷º"};
const unsigned char PY_mb_xin   []={"Ğ½Ğ¾Ğ¿ĞÀĞÁĞÂĞÃĞÄĞÅĞÆÜ°İ·ì§öÎê¿Ø¶âàïâ"};
const unsigned char PY_mb_xing  []={"ĞÒÊ¡ĞÇĞÈĞÉĞÊĞËĞÌĞÍĞÎĞÏĞĞĞÑĞÓĞÔĞÕâ¼ÚêÜôÜşß©ã¬íÊ"};
const unsigned char PY_mb_xiong []={"ĞÖĞ×ĞØĞÙĞÚĞÛĞÜÜº"};
const unsigned char PY_mb_xiu   []={"³ôËŞĞİĞŞĞßĞàĞáĞâĞãĞäĞåßİäåõ÷âÊá¶âÓğ¼÷Û"};
const unsigned char PY_mb_xu    []={"ĞøĞ÷ĞæĞçĞèĞéĞêĞëĞìĞíĞîĞïĞğĞñĞòĞóĞôĞõĞöÚ¼ìãÛÃÛ×Ş£äªä°äÓçïèòÓõñãíìôÚõ¯"};
const unsigned char PY_mb_xuan  []={"ĞşÑ¡ĞùĞúĞûäÖĞüĞıêÑÑ¤ìÅÑ£Ñ¢ÙØÚÎİæãùäöè¯é¸ìÓŞïíÛîçïàÈ¯"};
const unsigned char PY_mb_xue   []={"Ï÷Ñ¥Ñ¦Ñ§Ñ¨Ñ©Ñª÷¨ÚÊàåí´õ½"};
const unsigned char PY_mb_xun   []={"Ñ°Ñ®Ñ¸Ñ¶Ñ¯ÑµÑ«Ñ¬Ñ­Ñ±Ñ²Ñ³Ñ´Ñ·Û¨Û÷Ü÷Ş¹á¾áßõ¸öà¿£İ¡Ş¦â´Ùãâşä­ä±êÖñ¿"};
const unsigned char PY_mb_ya    []={"ÑÀÑ¿ÑÇÑÆÑ¹ÑÅÑºÑ»Ñ¼Ñ½Ñ¾ÑÂÑÃÑÄÑÈÔşØóÑÁÛëŞëá¬åÂæ«çğèâë²í¼íığéñâ"};
const unsigned char PY_mb_yan   []={"ÑÔÑİÑéÑáÑÏÑØÑ×ÑàÑÊÑËÑÙÑÚÑÛÑÌÑÍÑÎÑĞÑÒÑÓÑÕÑÖÑÜÑŞÑßÑâÑãÑäÑÉÑåÑæÑçÑèÑÑãÆåûæÌëÙëçìÍâûÙ²ÙÈÇ¦ÒóØÉØÍØßÙğÚ¥ÚİÚçÛ±Û³Ü¾İÎáÃ÷ÊãÕäÎäÙçüéÜêÌî»óÛõ¦÷Ğ÷ú÷ü"};
const unsigned char PY_mb_yang  []={"ÑëÑöÑòÑóÑôÑøÑùÑîÑïí¦ÑêÑìÑíÑğÑõÑñÑ÷Ñúáàâóãóì¾ìÈòÕ÷±"};
const unsigned char PY_mb_yao   []={"ÒªÑûÒ§Ò©ÑüÑıÒ¡Ò¢ëÈñºÒ£Ò¤Ò¥Ò¦Ò¨Ò«Ô¿Ø²Ø³çÛßºÑşÄöÅ±½ÄáÅáÊáæçòèÃé÷ê×ï¢ğÎôí÷¥"};
const unsigned char PY_mb_ye    []={"Ò²Ò³ÒµÒ¶Ò¹ÒºÒ¬Ò­Ò®Ò¯Ò°Ò±Ò´Ò·Ò¸Ğ°ÑÊÚËÖÑØÌÚşŞŞçğêÊìÇîô"};
const unsigned char PY_mb_yi    []={"Ò»ÒÒÒÑÒÔÒäÒåÒéÒêÒëÒìÒæÒ¼Ò½Ò¾Ò¿ÒÀÒÁÒÂÒÃÒÄÒÅÒÆÒÇÒÈÒÉÒÊÒËÒÌÒÍÒÎÒÏÒĞÒÓÒÕÒÖÒ×ÒØÒÙÒÚÒÛÒÜÒİÒŞÒßÒàÒáÒâÒãÒçÒèÒíÒî°¬Î²ÒïØ×ØæØıÙ«Ú±ÚâÛİÛüÜ²ÜÓÜèŞ²ŞÄŞÈŞÚß®ß½ß×ßŞàæá»áÚâ¢âÂâøâùã¨äôåÆæäçËéìéóêİì¥ì½ìÚíôîÆîèï×ïîğêğùñ¯ñ´ñÂòæô¯ôàôèôı÷ğ"};
const unsigned char PY_mb_yin   []={"ÒüÒıÓ¡ÒğÒñÒòÒóÒôÒõÒöÒ÷ÒøÒùÒúÒûÒşö¸Ø·ò¾Û´ÛÈÛóÜ§ÜáßÅà³áşâ¹ä¦äÎë³î÷ñ«ñ¿ö¯"};
const unsigned char PY_mb_ying  []={"Ó³Ó°Ó¢Ó¨Ó©ÓªÓ«Ó£Ó¤Ó¥Ó¦Ó§Ó¬Ó­Ó®Ó¯Ó±Ó²ÙøİºİÓğĞäëå­äŞçøÛ«ÜãÜşİöŞüàÓâßè¬éºëôñ¨ò£ó¿"};
const unsigned char PY_mb_yo    []={"Ó´Óıà¡"};
const unsigned char PY_mb_yong  []={"ÓÃÓµÓ¶ÓÂÓ¿Ó·Ó¸Ó¹ÓºÓ»Ó¼Ó½Ó¾ÓÀÓÁÙ¸ÛÕÜ­à¯ã¼çßïŞğ®÷«÷Ó"};
const unsigned char PY_mb_you   []={"ÓÈÓĞÓÖÓÕÓ×ÓÑÓÒÓÓÓÄÓÅÓÆÓÇÓÉÓÊÓËÓÌÓÍÓÎÓÏÓÔßÏğàöÏ÷î÷øòÄØüØÕÙ§İ¬İ¯İµŞÌàóå¶èÖéàë»îğòÊòöòøôí"};
const unsigned char PY_mb_yu    []={"ÓàÓëÓÚÓèÓîÓñÓêÓıÓşÔ¡ÓãÓØÓÙÓÛÓİÓŞÓßÓáÓâÓäÓåÓæÓçÓéÓìÓíÓïÓğÓòÓóÓôÓõÓöÓ÷ÓøÓùÓúÓÜÓûÓüÔ¢Ô£Ô¤Ô¥Ô¦óÄØ¹ÚÄì¶ÚÍÎµÎ¾Ø®ØñÙ¶İÇİÒİ÷ŞíàôàöáÎáüâÀâÅâ×ãĞå÷åıæ¥æúè¤êÅêìëéì£ìÏìÙìÛí±í²îÚğÁğÖğõğöñ¾ñÁòâòõô§ô¨ö§ö¹"};
const unsigned char PY_mb_yuan  []={"Ô­ÔªÔ°Ô±Ô²Ô´ÔµÔ¶Ô¸Ô¹ÔºÔ§Ô¨Ô©Ô«Ô¬Ô®Ô¯Ô³Ô·æÂÜ«Ü¾Şòà÷ãäè¥éÚë¼íóğ°ó¢óîö½"};

//#ifndef WIN_SIM
const unsigned char PY_mb_yue   []={"ÔÂÔÃÔÄÀÖËµÔ»Ô¼Ô½Ô¾Ô¿ÔÀÔÁÙßßÜå®èİéĞë¾îá"};//
//#endif

//#ifdef WIN_SIM
//const unsigned char PY_mb_yue   []={"ÔÂÔÃÔÄÀÖËµÔ»Ô¼Ô½Ô¾Ô¿ÔÀÔÁÙßßÜå®èİéĞë¾îá"};
//#endif

const unsigned char PY_mb_yun   []={"ÔÆÔ±ÔÊÔËÔÎÔÅÔÈÔÉÔÌÔÍìÙÔÏÔĞëµéæÜ¿ÔÇÛ©áñã¢ã³ç¡è¹êÀóŞ"};
const unsigned char PY_mb_za    []={"ÔÑÔÒÔÓÔúÕ¦ßÆŞÙ"};
const unsigned char PY_mb_zai   []={"ÔÙÔÚÔÔÔÕÔÖÔ×ÔØáÌçŞ"};
const unsigned char PY_mb_zan   []={"ÔÛÔÜÔİÔŞêÃô¢ŞÙè¶ôØôõöÉ"};
const unsigned char PY_mb_zang  []={"²ØÔßÔàÔáæàê°"};
const unsigned char PY_mb_zao   []={"ÔæÔâÔçÔìÔíÔîÔãÔäÔèÔêÔëÔïÔåÔéßğ"};
const unsigned char PY_mb_ze    []={"ÔğÔñÔòÔóÕ¦ØÆØÓßõàıåÅê¾óĞóåô·"};
const unsigned char PY_mb_zei   []={"Ôô"};
const unsigned char PY_mb_zen   []={"ÔõÚÚ"};
const unsigned char PY_mb_zeng  []={"ÔöÔ÷ÔøÔùçÕêµîÀï­"};
const unsigned char PY_mb_zha   []={"ÔúÕ¢²éÔûÔüÔıÔşÕ¡Õ£Õ¤Õ¥Õ¦Õ§Õ¨Õ©ß¸ßå×õŞêòÆßîà©é«íÄğäö´÷ş"};
const unsigned char PY_mb_zhai  []={"Õ¬Õ­Õ®µÔÔñÕªÕ«Õ¯íÎñ©"};
const unsigned char PY_mb_zhan  []={"Õ¼Õ½Õ¾Õ¹Õ´ÕÀÕ°Õ±Õ²Õ³ÕµÕ¶Õ·Õ¸Õº²üÕ»Õ¿ÚŞŞøæöì¹"};
const unsigned char PY_mb_zhang []={"ÕÅÕÉÕÌÕÍÕÈÕÁÕÂÕÃÕÄÕÆÕÇÕÊÕË³¤ÕÎÕÏá¤áÖâ¯ó¯ØëÛµæÑè°"};
const unsigned char PY_mb_zhao  []={"ÕÒÕÙ×¦×ÅÕ×³¯ÕĞÕÑÚ¯ÕÓÕÔÕÕÕÖÕØîÈóÉßúèş"};
const unsigned char PY_mb_zhe   []={"ÕÚÕÛÕÜÕİÕŞÕßÕàÕáÕâÕã×ÅÚØß¡èÏéüíİğÑñŞòØô÷"};
const unsigned char PY_mb_zhen  []={"ÕæÕêÕëÕğÕñÕïÕóÕòÕìÕíÕäÕîÕåÕçóğÕéÖ¡ÛÚÕèİèä¥äÚçÇèåé©é»éôêâëÓëŞìõî³ğ¡ğ²"};
const unsigned char PY_mb_zheng []={"ÕıÖ¤ÕôÕõÕöÕ÷ÕøÕùÕúÕûÕüÕşÖ¢Ö£Úºá¿áçîÛï£óİöë"};
const unsigned char PY_mb_zhi   []={"ÖÊÖÃÖÆÖÎÖ§Ö»Ê¶Ö´ÖµÖ¹ÖÁÖ¥Ö®Ö­Ö¼Ö½Ö¾Ö¦ÖªÖ«Ö¬Ö¯Ö°Ö±Ö²Ö³Ö¶Ö·Ö¸ÖºÖ¿ÖÀÖÂÖÄÖÅÖÇÖÈÖÉÖ¨Ö©ÖËÖÌÖÍÖÏè×ÜÆØ´ÚìÛ¤ÛúŞıàùáçâºâååéåëæïèÎèÙèäéòéùêŞëÕëùìíìóíéïôğºğëòÎôêõ¥õÅõÙõÜõôö£"};
const unsigned char PY_mb_zhong []={"ÖĞÖÚÖÒÖÓÖÔÖÕÖÖÖ×ÖØÖÙÖÑÚ£âìïñó®ô±õà"};
const unsigned char PY_mb_zhou  []={"ÖÛÖÜÖİÖŞÖßÖàÖáÖâÖãÖäÖåÖæÖçÖèİ§ßúæ¨æûç§ëĞíØô¦ôíôü"};
const unsigned char PY_mb_zhu   []={"Ö÷×¡×¢×£ÖñÖéÖêÖëÖìÖíÖîÖïÖğÖòÖóÖôÖõÖöÖøÖùÖúÖûÖüÖıÖş×¤ØùóÃóçÙªÊôÊõÛ¥ÜÑÜïä¨ä¾äóèÌéÆéÍìÄîùğæğññÒô¶ôãõî÷æØ¼"};
const unsigned char PY_mb_zhua  []={"×¥×¦ÎÎ"};
const unsigned char PY_mb_zhuai []={"×§×ª"};
const unsigned char PY_mb_zhuan []={"´«×¨×©×ª×«×¬×­ßùâÍãçò§"};
const unsigned char PY_mb_zhuang[]={"´±×®×¯×°×±×²×³×´ŞÊí°"};
const unsigned char PY_mb_zhui  []={"×µ×¶×·×¸×¹×ºã·æíçÄö¿"};
const unsigned char PY_mb_zhun  []={"×»×¼â½ëÆñ¸"};
const unsigned char PY_mb_zhuo  []={"×Å×½×¾×¿×À×Æ×Â×Ç×Ã×Á×ÄÙ¾ÚÂßªä·äÃåªìÌìúí½ïí"};
const unsigned char PY_mb_zi    []={"×Ô×Ó×Ö×Ğ×È×É×Ê×Ë×Ì×Í×Î×Ï×Ñ×Ò×Õö·æ¢Ö¨áÑÚÑÜëæÜç»è÷ê¢êßí§íöïÅïöñèóÊôÒôôõşö¤öö÷Ú"};
const unsigned char PY_mb_zong  []={"×Ú×Û×Ü×××Ø×Ù×İôÕÙÌèÈëê"};
const unsigned char PY_mb_zou   []={"×ß×à×á×ŞÚÁÚîÛ¸æãöí"};
const unsigned char PY_mb_zu    []={"×ã×â×æ×ç×è×é×ä×åÙŞİÏïß"};
const unsigned char PY_mb_zuan  []={"×êß¬×ëçÚõò"};
const unsigned char PY_mb_zui   []={"×î×ï×ì×íŞ©õş"};
const unsigned char PY_mb_zun   []={"×ğ×ñé×÷®ß¤"};
const unsigned char PY_mb_zuo   []={"×ó×ô×ö×÷×ø×ù×ò´éßò×õÚè×ÁàÜâôëÑìñíÄõ¡"};



//Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×é
struct PinYinPCB const PYRankTwoList_a[]=
{
	{"",PY_mb_a},
	{"i",PY_mb_ai},
	{"n",PY_mb_an},
	{"ng",PY_mb_ang},
	{"o",PY_mb_ao}
};


struct PinYinPCB const PYRankTwoList_b[]=
{
	{"a",PY_mb_ba},
	{"ai",PY_mb_bai},
	{"an",PY_mb_ban},
	{"ang",PY_mb_bang},
	{"ao",PY_mb_bao},
	{"ei",PY_mb_bei},
	{"en",PY_mb_ben},
	{"eng",PY_mb_beng},
	{"i",PY_mb_bi},
	{"ian",PY_mb_bian},
	{"iao",PY_mb_biao},
	{"ie",PY_mb_bie},
	{"in",PY_mb_bin},
	{"ing",PY_mb_bing},
	{"o",PY_mb_bo},
	{"u",PY_mb_bu}
};

struct PinYinPCB const PYRankTwoList_c[]=
{
	{"a",PY_mb_ca},
	{"ai",PY_mb_cai},
	{"an",PY_mb_can},
	{"ang",PY_mb_cang},
	{"ao",PY_mb_cao},
	{"e",PY_mb_ce},
	{"eng",PY_mb_ceng},
	{"ha",PY_mb_cha},
	{"hai",PY_mb_chai},
	{"han",PY_mb_chan},
	{"hang",PY_mb_chang},
	{"hao",PY_mb_chao},
	{"he",PY_mb_che},
	{"hen",PY_mb_chen},
	{"heng",PY_mb_cheng},
	{"hi",PY_mb_chi},
	{"hong",PY_mb_chong},
	{"hou",PY_mb_chou},
	{"hu",PY_mb_chu},
	{"huai",PY_mb_chuai},
	{"huan",PY_mb_chuan},
	{"huang",PY_mb_chuang},
	{"hui",PY_mb_chui},
	{"hun",PY_mb_chun},
	{"huo",PY_mb_chuo},
	{"i",PY_mb_ci},
	{"ong",PY_mb_cong},
	{"ou",PY_mb_cou},
	{"u",PY_mb_cu},
	{"uan",PY_mb_cuan},
	{"ui",PY_mb_cui},
	{"un",PY_mb_cun},
	{"uo",PY_mb_cuo}
};


struct PinYinPCB const PYRankTwoList_d[]={{"a   ",PY_mb_da},
                                    {"ai",PY_mb_dai},
                                    {"an",PY_mb_dan},
                                    {"ang",PY_mb_dang},
                                    {"ao",PY_mb_dao},
                                    {"e",PY_mb_de},
                                    {"eng",PY_mb_deng},
                                    {"i",PY_mb_di},
                                    {"ian",PY_mb_dian},
                                    {"iao",PY_mb_diao},
                                    {"ie",PY_mb_die},
                                    {"ing",PY_mb_ding},
                                    {"iu",PY_mb_diu},
                                    {"ong",PY_mb_dong},
                                    {"ou",PY_mb_dou},
                                    {"u",PY_mb_du},
                                    {"uan",PY_mb_duan},
                                    {"ui",PY_mb_dui},
                                    {"un",PY_mb_dun},
                                    {"uo",PY_mb_duo}};
struct PinYinPCB const PYRankTwoList_e[]={{"",PY_mb_e},
                                    {"n",PY_mb_en},
                                    {"r",PY_mb_er}};
struct PinYinPCB const PYRankTwoList_f[]={{"a",PY_mb_fa},
                                    {"an",PY_mb_fan},
                                    {"ang",PY_mb_fang},
                                    {"ei",PY_mb_fei},
                                    {"en",PY_mb_fen},
                                    {"eng",PY_mb_feng},
                                    {"o",PY_mb_fo},
                                    {"ou",PY_mb_fou},
                                    {"u",PY_mb_fu}};
struct PinYinPCB const PYRankTwoList_g[]={{"a",PY_mb_ga},
                                    {"ai",PY_mb_gai},
                                    {"an",PY_mb_gan},
                                    {"ang",PY_mb_gang},
                                    {"ao",PY_mb_gao},
                                    {"e",PY_mb_ge},
                                    {"ei",PY_mb_gei},
                                    {"en",PY_mb_gan},
                                    {"eng",PY_mb_geng},
                                    {"ong",PY_mb_gong},
                                    {"ou",PY_mb_gou},
                                    {"u",PY_mb_gu},
                                    {"ua",PY_mb_gua},
                                    {"uai",PY_mb_guai},
                                    {"uan",PY_mb_guan},
                                    {"uang",PY_mb_guang},
                                    {"ui",PY_mb_gui},
                                    {"un",PY_mb_gun},
                                    {"uo",PY_mb_guo}};
struct PinYinPCB const PYRankTwoList_h[]={{"a",PY_mb_ha},
                                    {"ai",PY_mb_hai},
                                    {"an",PY_mb_han},
                                    {"ang",PY_mb_hang},
                                    {"ao",PY_mb_hao},
                                    {"e",PY_mb_he},
                                    {"ei",PY_mb_hei},
                                    {"en",PY_mb_hen},
                                    {"eng",PY_mb_heng},
                                    {"ong",PY_mb_hong},
                                    {"ou",PY_mb_hou},
                                    {"u",PY_mb_hu},
                                    {"ua",PY_mb_hua},
                                    {"uai",PY_mb_huai},
                                    {"uan",PY_mb_huan},
                                    {"uang ",PY_mb_huang},
                                    {"ui",PY_mb_hui},
                                    {"un",PY_mb_hun},
                                    {"uo",PY_mb_huo}};
struct PinYinPCB const PYRankTwoList_i[]={"",PY_mb_space};
struct PinYinPCB const PYRankTwoList_j[]={{"i",PY_mb_ji},
                                    {"ia",PY_mb_jia},
                                    {"ian",PY_mb_jian},
                                    {"iang",PY_mb_jiang},
                                    {"iao",PY_mb_jiao},
                                    {"ie",PY_mb_jie},
                                    {"in",PY_mb_jin},
                                    {"ing",PY_mb_jing},
                                    {"iong",PY_mb_jiong},
                                    {"iu",PY_mb_jiu},
                                    {"u",PY_mb_ju},
                                    {"uan",PY_mb_juan},
                                    {"ue",PY_mb_jue},
                                    {"un",PY_mb_jun}};
struct PinYinPCB const PYRankTwoList_k[]={{"a",PY_mb_ka},
                                    {"ai",PY_mb_kai},
                                    {"an",PY_mb_kan},
                                    {"ang",PY_mb_kang},
                                    {"ao",PY_mb_kao},
                                    {"e",PY_mb_ke},
                                    {"en",PY_mb_ken},
                                    {"eng",PY_mb_keng},
                                    {"ong",PY_mb_kong},
                                    {"ou",PY_mb_kou},
                                    {"u",PY_mb_ku},
                                    {"ua",PY_mb_kua},
                                    {"uai",PY_mb_kuai},
                                    {"uan",PY_mb_kuan},
                                    {"uang",PY_mb_kuang},
                                    {"ui",PY_mb_kui},
                                    {"un",PY_mb_kun},
                                    {"uo",PY_mb_kuo}};
struct PinYinPCB const PYRankTwoList_l[]={{"a",PY_mb_la},
                                    {"ai",PY_mb_lai},
                                    {"an",PY_mb_lan},
                                    {"ang",PY_mb_lang},
                                    {"ao",PY_mb_lao},
                                    {"e",PY_mb_le},
                                    {"ei",PY_mb_lei},
                                    {"eng",PY_mb_leng},
                                    {"i",PY_mb_li},
                                    {"ian",PY_mb_lian},
                                    {"iang",PY_mb_liang},
                                    {"iao",PY_mb_liao},
                                    {"ie",PY_mb_lie},
                                    {"in",PY_mb_lin},
                                    {"ing",PY_mb_ling},
                                    {"iu",PY_mb_liu},
                                    {"ong",PY_mb_long},
                                    {"ou",PY_mb_lou},
                                    {"u",PY_mb_lu},
                                    {"uan",PY_mb_luan},
                                    {"ue",PY_mb_lue},
                                    {"un",PY_mb_lun},
                                    {"uo",PY_mb_luo},
                                    {"v",PY_mb_lv}};
struct PinYinPCB const PYRankTwoList_m[]={{"a",PY_mb_ma},
                                    {"ai",PY_mb_mai},
                                    {"an",PY_mb_man},
                                    {"ang",PY_mb_mang},
                                    {"ao",PY_mb_mao},
                                    {"e",PY_mb_me},
                                    {"ei",PY_mb_mei},
                                    {"en",PY_mb_men},
                                    {"eng",PY_mb_meng},
                                    {"i",PY_mb_mi},
                                    {"ian",PY_mb_mian},
                                    {"iao",PY_mb_miao},
                                    {"ie",PY_mb_mie},
                                    {"in",PY_mb_min},
                                    {"ing",PY_mb_ming},
                                    {"iu",PY_mb_miu},
                                    {"o",PY_mb_mo},
                                    {"ou",PY_mb_mou},
                                    {"u",PY_mb_mu}};
struct PinYinPCB const PYRankTwoList_n[]={{"a",PY_mb_na},
                                    {"ai",PY_mb_nai},
                                    {"an",PY_mb_nan},
                                    {"ang",PY_mb_nang},
                                    {"ao",PY_mb_nao},
                                    {"e",PY_mb_ne},
                                    {"ei",PY_mb_nei},
                                    {"en",PY_mb_nen},
                                    {"eng",PY_mb_neng},
                                    {"i",PY_mb_ni},
                                    {"ian",PY_mb_nian},
                                    {"iang",PY_mb_niang},
                                    {"iao",PY_mb_niao},
                                    {"ie",PY_mb_nie},
                                    {"in",PY_mb_nin},
                                    {"ing",PY_mb_ning},
                                    {"iu",PY_mb_niu},
                                    {"ong",PY_mb_nong},
                                    {"u",PY_mb_nu},
                                    {"uan",PY_mb_nuan},
                                    {"ue",PY_mb_nue},
                                    {"uo",PY_mb_nuo},
                                    {"v",PY_mb_nv}};
struct PinYinPCB const PYRankTwoList_o[]={{"",PY_mb_o},
                                    {"u",PY_mb_ou}};
struct PinYinPCB const PYRankTwoList_p[]={{"a",PY_mb_pa},
                                    {"ai",PY_mb_pai},
                                    {"an",PY_mb_pan},
                                    {"ang",PY_mb_pang},
                                    {"ao",PY_mb_pao},
                                    {"ei",PY_mb_pei},
                                    {"en",PY_mb_pen},
                                    {"eng",PY_mb_peng},
                                    {"i",PY_mb_pi},
                                    {"ian",PY_mb_pian},
                                    {"iao",PY_mb_piao},
                                    {"ie",PY_mb_pie},
                                    {"in",PY_mb_pin},
                                    {"ing",PY_mb_ping},
                                    {"o",PY_mb_po},
                                    {"ou",PY_mb_pou},
                                    {"u",PY_mb_pu}};
struct PinYinPCB const PYRankTwoList_q[]={{"i",PY_mb_qi},
                                    {"ia",PY_mb_qia},
                                    {"ian",PY_mb_qian},
                                    {"iang",PY_mb_qiang},
                                    {"iao",PY_mb_qiao},
                                    {"ie",PY_mb_qie},
                                    {"in",PY_mb_qin},
                                    {"ing",PY_mb_qing},
                                    {"iong",PY_mb_qiong},
                                    {"iu",PY_mb_qiu},
                                    {"u",PY_mb_qu},
                                    {"uan",PY_mb_quan},
                                    {"ue",PY_mb_que},
                                    {"un",PY_mb_qun}};
struct PinYinPCB const PYRankTwoList_r[]={{"an",PY_mb_ran},
                                    {"ang",PY_mb_rang},
                                    {"ao",PY_mb_rao},
                                    {"e",PY_mb_re},
                                    {"en",PY_mb_ren},
                                    {"eng",PY_mb_reng},
                                    {"i",PY_mb_ri},
                                    {"ong",PY_mb_rong},
                                    {"ou",PY_mb_rou},
                                    {"u",PY_mb_ru},
                                    {"uan",PY_mb_ruan},
                                    {"ui",PY_mb_rui},
                                    {"un",PY_mb_run},
                                    {"uo",PY_mb_ruo}};
struct PinYinPCB const PYRankTwoList_s[]={{"a",PY_mb_sa},
                                    {"ai",PY_mb_sai},
                                    {"an",PY_mb_san},
                                    {"ang",PY_mb_sang},
                                    {"ao",PY_mb_sao},
                                    {"e",PY_mb_se},
                                    {"en",PY_mb_sen},
                                    {"eng",PY_mb_seng},
                                    {"ha",PY_mb_sha},
                                    {"hai",PY_mb_shai},
                                    {"han",PY_mb_shan},
                                    {"hang ",PY_mb_shang},
                                    {"hao",PY_mb_shao},
                                    {"he",PY_mb_she},
                                    {"hen",PY_mb_shen},
                                    {"heng",PY_mb_sheng},
                                    {"hi",PY_mb_shi},
                                    {"hou",PY_mb_shou},
                                    {"hu",PY_mb_shu},
                                    {"hua",PY_mb_shua},
                                    {"huai",PY_mb_shuai},
                                    {"huan",PY_mb_shuan},
                                    {"huang",PY_mb_shuang},
                                    {"hui",PY_mb_shui},
                                    {"hun",PY_mb_shun},
                                    {"huo",PY_mb_shuo},
                                    {"i",PY_mb_si},
                                    {"ong",PY_mb_song},
                                    {"ou",PY_mb_sou},
                                    {"u",PY_mb_su},
                                    {"uan",PY_mb_suan},
                                    {"ui",PY_mb_sui},
                                    {"un",PY_mb_sun},
                                    {"uo",PY_mb_suo}};
struct PinYinPCB const PYRankTwoList_t[]={{"a",PY_mb_ta},
                                    {"ai",PY_mb_tai},
                                    {"an",PY_mb_tan},
                                    {"ang",PY_mb_tang},
                                    {"ao",PY_mb_tao},
                                    {"e",PY_mb_te},
                                    {"eng",PY_mb_teng},
                                    {"i",PY_mb_ti},
                                    {"ian",PY_mb_tian},
                                    {"iao",PY_mb_tiao},
                                    {"ie",PY_mb_tie},
                                    {"ing",PY_mb_ting},
                                    {"ong",PY_mb_tong},
                                    {"ou",PY_mb_tou},
                                    {"u",PY_mb_tu},
                                    {"uan",PY_mb_tuan},
                                    {"ui",PY_mb_tui},
                                    {"un",PY_mb_tun},
                                    {"uo",PY_mb_tuo}};
struct PinYinPCB const PYRankTwoList_u[]={{"",PY_mb_space}};
struct PinYinPCB const PYRankTwoList_v[]={{"",PY_mb_space}};
struct PinYinPCB const PYRankTwoList_w[]={{"a",PY_mb_wa},
                                    {"ai",PY_mb_wai},
                                    {"an",PY_mb_wan},
                                    {"ang",PY_mb_wang},
                                    {"ei",PY_mb_wei},
                                    {"en",PY_mb_wen},
                                    {"eng",PY_mb_weng},
                                    {"o",PY_mb_wo},
                                    {"u",PY_mb_wu}};
struct PinYinPCB const PYRankTwoList_x[]={{"i",PY_mb_xi},
                                    {"ia",PY_mb_xia},
                                    {"ian",PY_mb_xian},
                                    {"iang",PY_mb_xiang},
                                    {"iao",PY_mb_xiao},
                                    {"ie",PY_mb_xie},
                                    {"in",PY_mb_xin},
                                    {"ing",PY_mb_xing},
                                    {"iong",PY_mb_xiong},
                                    {"iu",PY_mb_xiu},
                                    {"u",PY_mb_xu},
                                    {"uan",PY_mb_xuan},
                                    {"ue",PY_mb_xue},
                                    {"un",PY_mb_xun}};
struct PinYinPCB const PYRankTwoList_y[]={{"a",PY_mb_ya},
                                    {"an",PY_mb_yan},
                                    {"ang",PY_mb_yang},
                                    {"ao",PY_mb_yao},
                                    {"e",PY_mb_ye},
                                    {"i",PY_mb_yi},
                                    {"in",PY_mb_yin},
                                    {"ing",PY_mb_ying},
                                    {"o",PY_mb_yo},
                                    {"ong",PY_mb_yong},
                                    {"ou",PY_mb_you},
                                    {"u",PY_mb_yu},
                                    {"uan",PY_mb_yuan},
                                    {"ue",PY_mb_yue},
                                    {"un",PY_mb_yun}};
struct PinYinPCB const PYRankTwoList_z[]={{"a",PY_mb_za},
                                    {"ai",PY_mb_zai},
                                    {"an",PY_mb_zan},
                                    {"ang",PY_mb_zang},
                                    {"ao",PY_mb_zao},
                                    {"e",PY_mb_ze},
                                    {"ei",PY_mb_zei},
                                    {"en",PY_mb_zen},
                                    {"eng",PY_mb_zeng},
                                    {"ha",PY_mb_zha},
                                    {"hai",PY_mb_zhai},
                                    {"han",PY_mb_zhan},
                                    {"hang",PY_mb_zhang},
                                    {"hao",PY_mb_zhao},
                                    {"he",PY_mb_zhe},
                                    {"hen",PY_mb_zhen},
                                    {"heng",PY_mb_zheng},
                                    {"hi",PY_mb_zhi},
                                    {"hong",PY_mb_zhong},
                                    {"hou",PY_mb_zhou},
                                    {"hu",PY_mb_zhu},
                                    {"hua",PY_mb_zhua},
                                    {"huai",PY_mb_zhuai},
                                    {"huan",PY_mb_zhuan},
                                    {"huang",PY_mb_zhuang},
                                    {"hui",PY_mb_zhui},
                                    {"hun",PY_mb_zhun},
                                    {"huo",PY_mb_zhuo},
                                    {"i",PY_mb_zi},
                                    {"ong",PY_mb_zong},
                                    {"ou",PY_mb_zou},
                                    {"u",PY_mb_zu},
                                    {"uan",PY_mb_zuan},
                                    {"ui",PY_mb_zui},
                                    {"un",PY_mb_zun},
                                    {"uo",PY_mb_zuo}};
struct PinYinPCB const PYRankTwoList_end[]={"",PY_mb_space};
//Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×éµÄÖ¸Õë
struct PinYinPCB const *PYRankThreeList[]={  PYRankTwoList_a,
                                            PYRankTwoList_b,
                                            PYRankTwoList_c,
                                            PYRankTwoList_d,
                                            PYRankTwoList_e,
                                            PYRankTwoList_f,
                                            PYRankTwoList_g,
                                            PYRankTwoList_h,
                                            PYRankTwoList_i,
                                            PYRankTwoList_j,
                                            PYRankTwoList_k,
                                            PYRankTwoList_l,
                                            PYRankTwoList_m,
                                            PYRankTwoList_n,
                                            PYRankTwoList_o,
                                            PYRankTwoList_p,
                                            PYRankTwoList_q,
                                            PYRankTwoList_r,
                                            PYRankTwoList_s,
                                            PYRankTwoList_t,
                                            PYRankTwoList_u,
                                            PYRankTwoList_v,
                                            PYRankTwoList_w,
                                            PYRankTwoList_x,
                                            PYRankTwoList_y,
                                            PYRankTwoList_z,
                                            PYRankTwoList_end
										};


#if 0




//b
PinYinDef const PYRankTwoList_b[]=
{
	{"ba",		sizeof(PY_mb_ba)/2,		PY_mb_ba},
	{"bai",		sizeof(PY_mb_bai)/2,		PY_mb_bai},
	{"ban",		sizeof(PY_mb_ban)/2,		PY_mb_ban},
	{"bang",	sizeof(PY_mb_bang)/2,	PY_mb_bang},	
	{"bao",		sizeof(PY_mb_bao)/2,		PY_mb_bao},	
	{"bei",		sizeof(PY_mb_bei)/2,		PY_mb_bei},
	{"ben",		sizeof(PY_mb_ben)/2,		PY_mb_ben},
	{"beng",	sizeof(PY_mb_beng)/2,	PY_mb_beng},
	{"bi",		sizeof(PY_mb_bi)/2,		PY_mb_bi},
	{"bian",		sizeof(PY_mb_bian)/2,	PY_mb_bian},
	{"biao",		sizeof(PY_mb_biao)/2,	PY_mb_biao},
	{"bie",		sizeof(PY_mb_bie)/2,		PY_mb_bie},
	{"bin",		sizeof(PY_mb_bin)/2,		PY_mb_bin},
	{"bing",		sizeof(PY_mb_bing)/2,	PY_mb_bing},
	{"bo",		sizeof(PY_mb_bo)/2,		PY_mb_bo},
	{"bu",		sizeof(PY_mb_bu)/2,		PY_mb_bu},	
};	








//c
PinYinDef const PYRankTwoList_c[]=
{
	{"ca",		sizeof(PY_mb_ca)/2,		PY_mb_ca},
	{"cai",		sizeof(PY_mb_cai)/2,		PY_mb_cai},
	{"can",		sizeof(PY_mb_can)/2,		PY_mb_can},
	{"cang",		sizeof(PY_mb_cang)/2,	PY_mb_cang},	
	{"cao",		sizeof(PY_mb_cao)/2,		PY_mb_cao},
	{"ce",		sizeof(PY_mb_ce)/2,		PY_mb_ce},
	{"cen",		sizeof(PY_mb_cen)/2,		PY_mb_cen},
	{"ceng",		sizeof(PY_mb_ceng)/2,	PY_mb_ceng},
	{"cha",		sizeof(PY_mb_cha)/2,		PY_mb_cha},
	{"chai",		sizeof(PY_mb_chai)/2,	PY_mb_chai},
	{"chan",		sizeof(PY_mb_chan)/2,	PY_mb_chan},
	{"chang",	sizeof(PY_mb_chang)/2,	PY_mb_chang},
	{"chao",		sizeof(PY_mb_chao)/2,	PY_mb_chao},
	{"che",		sizeof(PY_mb_che)/2,		PY_mb_che},
	{"chen",		sizeof(PY_mb_chen)/2,	PY_mb_chen},
	{"cheng",	sizeof(PY_mb_cheng)/2,	PY_mb_cheng},
	{"chi",		sizeof(PY_mb_chi)/2,		PY_mb_chi},	
	{"chong",	sizeof(PY_mb_chong)/2,	PY_mb_chong},
	{"chou",		sizeof(PY_mb_chou)/2,	PY_mb_chou},
	{"chu",		sizeof(PY_mb_chu)/2,		PY_mb_chu},
	{"chuai",	sizeof(PY_mb_chuai)/2,	PY_mb_chuai},
	{"chuan",	sizeof(PY_mb_chuan)/2,	PY_mb_chuan},
	{"chuang",	sizeof(PY_mb_chuang)/2,PY_mb_chuang},
	{"chui",		sizeof(PY_mb_chui)/2,	PY_mb_chui},
	{"chun",		sizeof(PY_mb_chun)/2,	PY_mb_chun},
	{"chuo",		sizeof(PY_mb_chuo)/2,	PY_mb_chuo},
	{"ci",		sizeof(PY_mb_ci)/2,		PY_mb_ci},
	{"cong",		sizeof(PY_mb_cong)/2,	PY_mb_cong},
	{"cou",		sizeof(PY_mb_cou)/2,		PY_mb_cou},
	{"cu",		sizeof(PY_mb_cu)/2,		PY_mb_cu},	
	{"cuan",		sizeof(PY_mb_cuan)/2,	PY_mb_cuan},	
	{"cui",		sizeof(PY_mb_cui)/2,		PY_mb_cui},
	{"cun",		sizeof(PY_mb_cun)/2,		PY_mb_cun},
	{"cuo",		sizeof(PY_mb_cuo)/2,		PY_mb_cuo},
};	

//d
PinYinDef const PYRankTwoList_d[]=
{
	{"da",		sizeof(PY_mb_da)/2,		PY_mb_da},
	{"dai",		sizeof(PY_mb_dai)/2,		PY_mb_dai},
	{"dan",		sizeof(PY_mb_dan)/2,		PY_mb_dan},
	{"dang",	sizeof(PY_mb_dang)/2,	PY_mb_dang},
	{"dao",		sizeof(PY_mb_dao)/2,		PY_mb_dao},
	{"de",		sizeof(PY_mb_de)/2,		PY_mb_de},
	{"dei",		sizeof(PY_mb_dei)/2,		PY_mb_dei},
	{"deng",	sizeof(PY_mb_deng)/2,	PY_mb_deng},
	{"di",		sizeof(PY_mb_di)/2,		PY_mb_di},
	{"dia",		sizeof(PY_mb_dia)/2,		PY_mb_dia},
	{"dian",		sizeof(PY_mb_dian)/2,	PY_mb_dian},
	{"diao",		sizeof(PY_mb_diao)/2,	PY_mb_diao},
	{"die",		sizeof(PY_mb_die)/2,		PY_mb_die},
	{"ding",		sizeof(PY_mb_ding)/2,	PY_mb_ding},
	{"diu",		sizeof(PY_mb_diu)/2,		PY_mb_diu},
	{"dong",	sizeof(PY_mb_dong)/2,	PY_mb_dong},
	{"dou",		sizeof(PY_mb_dou)/2,	PY_mb_dou},
	{"du",		sizeof(PY_mb_du)/2,		PY_mb_du},
	{"duan",	sizeof(PY_mb_duan)/2,	PY_mb_duan},
	{"dui",		sizeof(PY_mb_dui)/2,		PY_mb_dui},
	{"dun",		sizeof(PY_mb_dun)/2,	PY_mb_dun},
	{"duo",		sizeof(PY_mb_duo)/2,	PY_mb_duo},
	{"duo",		sizeof(PY_mb_duo)/2,	PY_mb_duo},
};

//e
PinYinDef const PYRankTwoList_e[]=
{
	{"e",		sizeof(PY_mb_e)/2,		PY_mb_e},
	{"ei",		sizeof(PY_mb_ei)/2,		PY_mb_ei},
	{"en",		sizeof(PY_mb_en)/2,		PY_mb_en},
	{"er",		sizeof(PY_mb_er)/2,		PY_mb_er},
};

//f
PinYinDef const PYRankTwoList_f[]=
{
	{"fa",		sizeof(PY_mb_fa)/2,		PY_mb_fa},
	{"fan",		sizeof(PY_mb_fan)/2,		PY_mb_fan},
	{"fang",		sizeof(PY_mb_fang)/2,	PY_mb_fang},
	{"fei",		sizeof(PY_mb_fei)/2,		PY_mb_fei},
	{"fen",		sizeof(PY_mb_fen)/2,		PY_mb_fen},
	{"feng",		sizeof(PY_mb_feng)/2,	PY_mb_feng},
	{"fo",		sizeof(PY_mb_fo)/2,		PY_mb_fo},
	{"fou",		sizeof(PY_mb_fou)/2,		PY_mb_fou},
	{"fu",		sizeof(PY_mb_fu)/2,		PY_mb_fu},
};

//g
PinYinDef const PYRankTwoList_g[]=
{
	{"ga",		sizeof(PY_mb_ga)/2,		PY_mb_ga},
	{"gai",		sizeof(PY_mb_gai)/2,		PY_mb_gai},
	{"gan",		sizeof(PY_mb_gan)/2,		PY_mb_gan},
	{"gang",	sizeof(PY_mb_gang)/2,	PY_mb_gang},
	{"gao",		sizeof(PY_mb_gao)/2,		PY_mb_gao},
	{"ge",		sizeof(PY_mb_ge)/2,		PY_mb_ge},
	{"gei",		sizeof(PY_mb_gei)/2,		PY_mb_gei},
	{"gen",		sizeof(PY_mb_gen)/2,		PY_mb_gen},
	{"geng",	sizeof(PY_mb_geng)/2,	PY_mb_geng},
	{"gong",	sizeof(PY_mb_gong)/2,	PY_mb_gong},
	{"gou",		sizeof(PY_mb_gou)/2,	PY_mb_gou},
	{"gu",		sizeof(PY_mb_gu)/2,		PY_mb_gu},
	{"gua",		sizeof(PY_mb_gua)/2,		PY_mb_gua},
	{"guai",		sizeof(PY_mb_guai)/2,	PY_mb_guai},
	{"guan",	sizeof(PY_mb_guan)/2,	PY_mb_guan},
	{"guang",	sizeof(PY_mb_guang)/2,	PY_mb_guang},
	{"gui",		sizeof(PY_mb_gui)/2,		PY_mb_gui},
	{"gun",		sizeof(PY_mb_gun)/2,	PY_mb_gun},
	{"guo",		sizeof(PY_mb_guo)/2,	PY_mb_guo},
};

//h
PinYinDef const PYRankTwoList_h[]=
{
	{"ha",		sizeof(PY_mb_ha)/2,		PY_mb_ha},
	{"hai",		sizeof(PY_mb_hai)/2,		PY_mb_hai},
	{"han",		sizeof(PY_mb_han)/2,		PY_mb_han},
	{"hang",	sizeof(PY_mb_hang)/2,	PY_mb_hang},
	{"hao",		sizeof(PY_mb_hao)/2,		PY_mb_hao},
	{"he",		sizeof(PY_mb_he)/2,		PY_mb_he},
	{"hei",		sizeof(PY_mb_hei)/2,		PY_mb_hei},
	{"hen",		sizeof(PY_mb_hen)/2,		PY_mb_hen},
	{"heng",	sizeof(PY_mb_heng)/2,	PY_mb_heng},
	{"hong",	sizeof(PY_mb_hong)/2,	PY_mb_hong},
	{"hou",		sizeof(PY_mb_hou)/2,	PY_mb_hou},
	{"hu",		sizeof(PY_mb_hu)/2,		PY_mb_hu},
	{"hua",		sizeof(PY_mb_hua)/2,		PY_mb_hua},
	{"huai",		sizeof(PY_mb_huai)/2,	PY_mb_huai},
	{"huan",	sizeof(PY_mb_huan)/2,	PY_mb_huan},
	{"huang",	sizeof(PY_mb_huang)/2,	PY_mb_huang},
	{"hui",		sizeof(PY_mb_hui)/2,		PY_mb_hui},
	{"hun",		sizeof(PY_mb_hun)/2,	PY_mb_hun},
	{"huo",		sizeof(PY_mb_huo)/2,	PY_mb_huo},
};

//i
PinYinDef PYRankTwoList_i[]={" ",sizeof(PY_mb_space)/2,PY_mb_space};

//j
PinYinDef const PYRankTwoList_j[]=
{
	{"ji",		sizeof(PY_mb_ji)/2,		PY_mb_ji},
	{"jia",		sizeof(PY_mb_jia)/2,		PY_mb_jia},
	{"jian",		sizeof(PY_mb_jian)/2,		PY_mb_jian},
	{"jiang",		sizeof(PY_mb_jiang)/2,	PY_mb_jiang},
	{"jiao",		sizeof(PY_mb_jiao)/2,		PY_mb_jiao},
	{"jie",		sizeof(PY_mb_jie)/2,		PY_mb_jie},
	{"jin",		sizeof(PY_mb_jin)/2,		PY_mb_jin},
	{"jing",		sizeof(PY_mb_jing)/2,		PY_mb_jing},
	{"jiong",		sizeof(PY_mb_jiong)/2,	PY_mb_jiong},
	{"jiu",		sizeof(PY_mb_jiu)/2,		PY_mb_jiu},
	{"ju",		sizeof(PY_mb_ju)/2,		PY_mb_ju},
	{"juan",		sizeof(PY_mb_juan)/2,	PY_mb_juan},
	{"jue",		sizeof(PY_mb_jue)/2,		PY_mb_jue},
	{"jun",		sizeof(PY_mb_jun)/2,		PY_mb_jun},
};

//k
PinYinDef const PYRankTwoList_k[]=
{
	{"ka",		sizeof(PY_mb_ka)/2,		PY_mb_ka},
	{"kai",		sizeof(PY_mb_kai)/2,		PY_mb_kai},
	{"kan",		sizeof(PY_mb_kan)/2,		PY_mb_kan},
	{"kang",		sizeof(PY_mb_kang)/2,	PY_mb_kang},
	{"kao",		sizeof(PY_mb_kao)/2,		PY_mb_kao},
	{"ke",		sizeof(PY_mb_ke)/2,		PY_mb_ke},
	{"ken",		sizeof(PY_mb_ken)/2,		PY_mb_ken},
	{"keng",		sizeof(PY_mb_keng)/2,	PY_mb_keng},
	{"kong",	sizeof(PY_mb_kong)/2,	PY_mb_kong},
	{"kou",		sizeof(PY_mb_kou)/2,		PY_mb_kou},
	{"ku",		sizeof(PY_mb_ku)/2,		PY_mb_ku},
	{"kua",		sizeof(PY_mb_kua)/2,		PY_mb_kua},
	{"kuai",		sizeof(PY_mb_kuai)/2,	PY_mb_kuai},
	{"kuan",		sizeof(PY_mb_kuan)/2,	PY_mb_kuan},
	{"kuang",	sizeof(PY_mb_kuang)/2,	PY_mb_kuang},
	{"kui",		sizeof(PY_mb_kui)/2,		PY_mb_kui},
	{"kun",		sizeof(PY_mb_kun)/2,		PY_mb_kun},
	{"kuo",		sizeof(PY_mb_kuo)/2,		PY_mb_kuo},
};

//l
PinYinDef const PYRankTwoList_l[]=
{
	{"la",		sizeof(PY_mb_la)/2,		PY_mb_la},
	{"lai",		sizeof(PY_mb_lai)/2,		PY_mb_lai},
	{"lan",		sizeof(PY_mb_lan)/2,		PY_mb_lan},
	{"lang",		sizeof(PY_mb_lang)/2,	PY_mb_lang},
	{"lao",		sizeof(PY_mb_lao)/2,		PY_mb_lao},
	{"lei",		sizeof(PY_mb_lei)/2,		PY_mb_lei},
	{"leng",		sizeof(PY_mb_leng)/2,	PY_mb_leng},
	{"li",		sizeof(PY_mb_li)/2,		PY_mb_li},
	{"lia",		sizeof(PY_mb_lia)/2,		PY_mb_lia},
	{"lian",		sizeof(PY_mb_lian)/2,		PY_mb_lian},
	{"liang",		sizeof(PY_mb_liang)/2,	PY_mb_liang},
	{"liao",		sizeof(PY_mb_liao)/2,		PY_mb_liao},
	{"lie",		sizeof(PY_mb_lie)/2,		PY_mb_lie},
	{"lin",		sizeof(PY_mb_lin)/2,		PY_mb_lin},
	{"ling",		sizeof(PY_mb_ling)/2,		PY_mb_ling},
	{"liu",		sizeof(PY_mb_liu)/2,		PY_mb_liu},
	{"lo",		sizeof(PY_mb_lo)/2,		PY_mb_lo},
	{"long",		sizeof(PY_mb_long)/2,	PY_mb_long},
	{"lou",		sizeof(PY_mb_lou)/2,		PY_mb_lou},
	{"lu",		sizeof(PY_mb_lu)/2,		PY_mb_lu},
	{"lv",		sizeof(PY_mb_lv)/2,		PY_mb_lv},
	{"luan",		sizeof(PY_mb_luan)/2,	PY_mb_luan},
	{"lue",		sizeof(PY_mb_lue)/2,		PY_mb_lue},
	{"lun",		sizeof(PY_mb_lun)/2,		PY_mb_lun},
	{"luo",		sizeof(PY_mb_luo)/2,		PY_mb_luo},
};

//m
PinYinDef const PYRankTwoList_m[]=
{
	{"m",		sizeof(PY_mb_m)/2,		PY_mb_m},
	{"ma",		sizeof(PY_mb_ma)/2,		PY_mb_ma},
	{"mai",		sizeof(PY_mb_mai)/2,		PY_mb_mai},
	{"man",		sizeof(PY_mb_man)/2,	PY_mb_man},
	{"mang",	sizeof(PY_mb_mang)/2,	PY_mb_mang},
	{"mao",		sizeof(PY_mb_mao)/2,	PY_mb_mao},
	{"me",		sizeof(PY_mb_me)/2,		PY_mb_me},
	{"mei",		sizeof(PY_mb_mei)/2,		PY_mb_mei},
	{"men",		sizeof(PY_mb_men)/2,	PY_mb_men},
	{"meng",	sizeof(PY_mb_meng)/2,	PY_mb_meng},
	{"mi",		sizeof(PY_mb_mi)/2,		PY_mb_mi},
	{"mian",		sizeof(PY_mb_mian)/2,	PY_mb_mian},
	{"miao",		sizeof(PY_mb_miao)/2,	PY_mb_miao},
	{"mie",		sizeof(PY_mb_mie)/2,		PY_mb_mie},
	{"min",		sizeof(PY_mb_min)/2,		PY_mb_min},
	{"ming",	sizeof(PY_mb_ming)/2,	PY_mb_ming},
	{"miu",		sizeof(PY_mb_miu)/2,		PY_mb_miu},
	{"mo",		sizeof(PY_mb_mo)/2,		PY_mb_mo},
	{"mou",		sizeof(PY_mb_mou)/2,	PY_mb_mou},
	{"mu",		sizeof(PY_mb_mu)/2,		PY_mb_mu},
};

//n
PinYinDef const PYRankTwoList_n[]=
{
	{"na",		sizeof(PY_mb_na)/2,		PY_mb_na},
	{"nai",		sizeof(PY_mb_nai)/2,		PY_mb_nai},
	{"nan",		sizeof(PY_mb_nan)/2,		PY_mb_nan},
	{"nang",	sizeof(PY_mb_nang)/2,	PY_mb_nang},
	{"nao",		sizeof(PY_mb_nao)/2,		PY_mb_nao},
	{"ne",		sizeof(PY_mb_ne)/2,		PY_mb_ne},
	{"nei",		sizeof(PY_mb_nei)/2,		PY_mb_nei},
	{"nen",		sizeof(PY_mb_nen)/2,		PY_mb_nen},
	{"neng",	sizeof(PY_mb_neng)/2,	PY_mb_neng},
	{"ng",		sizeof(PY_mb_ng)/2,		PY_mb_ng},
	{"ni",		sizeof(PY_mb_ni)/2,		PY_mb_ni},
	{"nian",		sizeof(PY_mb_nian)/2,	PY_mb_nian},
	{"niang",	sizeof(PY_mb_niang)/2,	PY_mb_niang},
	{"niao",		sizeof(PY_mb_niao)/2,	PY_mb_niao},
	{"nie",		sizeof(PY_mb_nie)/2,		PY_mb_nie},
	{"nin",		sizeof(PY_mb_nin)/2,		PY_mb_nin},	
	{"ning",		sizeof(PY_mb_ning)/2,	PY_mb_ning},
	{"niu",		sizeof(PY_mb_niu)/2,		PY_mb_niu},
	{"nong",	sizeof(PY_mb_nong)/2,	PY_mb_nong},
	{"nou",		sizeof(PY_mb_nou)/2,	PY_mb_nou},
	{"nu",		sizeof(PY_mb_nu)/2,		PY_mb_nu},
	{"nuan",	sizeof(PY_mb_nuan)/2,	PY_mb_nuan},
	{"nue",		sizeof(PY_mb_nue)/2,		PY_mb_nue},
	{"nuo",		sizeof(PY_mb_nuo)/2,	PY_mb_nuo},
	{"nv",		sizeof(PY_mb_nv)/2,		PY_mb_nv},
};

//o
PinYinDef const PYRankTwoList_o[]=
{
	{"o",		sizeof(PY_mb_o)/2,		PY_mb_o},
	{"ou",		sizeof(PY_mb_ou)/2,		PY_mb_ou},
};

//p
PinYinDef const PYRankTwoList_p[]=
{
	{"pa",		sizeof(PY_mb_pa)/2,		PY_mb_pa},
	{"pai",		sizeof(PY_mb_pai)/2,		PY_mb_pai},
	{"pan",		sizeof(PY_mb_pan)/2,		PY_mb_pan},
	{"pang",	sizeof(PY_mb_pang)/2,	PY_mb_pang},
	{"pao",		sizeof(PY_mb_pao)/2,		PY_mb_pao},
	{"pei",		sizeof(PY_mb_pei)/2,		PY_mb_pei},
	{"pen",		sizeof(PY_mb_pen)/2,		PY_mb_pen},
	{"peng",	sizeof(PY_mb_peng)/2,	PY_mb_peng},
	{"pi",		sizeof(PY_mb_pi)/2,		PY_mb_pi},
	{"pian",		sizeof(PY_mb_pian)/2,	PY_mb_pian},
	{"piao",		sizeof(PY_mb_piao)/2,	PY_mb_piao},
	{"pie",		sizeof(PY_mb_pie)/2,		PY_mb_pie},
	{"pin",		sizeof(PY_mb_pin)/2,		PY_mb_pin},
	{"ping",		sizeof(PY_mb_ping)/2,	PY_mb_ping},
	{"po",		sizeof(PY_mb_po)/2,		PY_mb_po},
	{"pou",		sizeof(PY_mb_pou)/2,	PY_mb_pou},
	{"pu",		sizeof(PY_mb_pu)/2,		PY_mb_pu},
};

//q
PinYinDef const PYRankTwoList_q[]=
{
	{"qi",		sizeof(PY_mb_qi)/2,		PY_mb_qi},
	{"qia",		sizeof(PY_mb_qia)/2,		PY_mb_qia},
	{"qian",		sizeof(PY_mb_qian)/2,	PY_mb_qian},
	{"qiang",	sizeof(PY_mb_qiang)/2,	PY_mb_qiang},
	{"qiao",		sizeof(PY_mb_qiao)/2,	PY_mb_qiao},
	{"qie",		sizeof(PY_mb_qie)/2,		PY_mb_qie},
	{"qin",		sizeof(PY_mb_qin)/2,		PY_mb_qin},
	{"qing",		sizeof(PY_mb_qing)/2,	PY_mb_qing},
	{"qiong",	sizeof(PY_mb_qiong)/2,	PY_mb_qiong},
	{"qiu",		sizeof(PY_mb_qiu)/2,		PY_mb_qiu},
	{"qu",		sizeof(PY_mb_qu)/2,		PY_mb_qu},
	{"quan",	sizeof(PY_mb_quan)/2,	PY_mb_quan},
	{"que",		sizeof(PY_mb_que)/2,		PY_mb_que},
	{"qun",		sizeof(PY_mb_qun)/2,	PY_mb_qun},
};

//r
PinYinDef const PYRankTwoList_r[]=
{
	{"ran",		sizeof(PY_mb_ran)/2,		PY_mb_ran},
	{"rang",		sizeof(PY_mb_rang)/2,	PY_mb_rang},
	{"rao",		sizeof(PY_mb_rao)/2,		PY_mb_rao},
	{"re",		sizeof(PY_mb_re)/2,		PY_mb_re},
	{"ren",		sizeof(PY_mb_ren)/2,		PY_mb_ren},
	{"reng",		sizeof(PY_mb_reng)/2,	PY_mb_reng},
	{"ri",		sizeof(PY_mb_ri)/2,		PY_mb_ri},
	{"rong",		sizeof(PY_mb_rong)/2,	PY_mb_rong},
	{"rou",		sizeof(PY_mb_rou)/2,		PY_mb_rou},
	{"ru",		sizeof(PY_mb_ru)/2,		PY_mb_ru},
	{"ruan",		sizeof(PY_mb_ruan)/2,	PY_mb_ruan},
	{"rui",		sizeof(PY_mb_rui)/2,		PY_mb_rui},
	{"run",		sizeof(PY_mb_run)/2,		PY_mb_run},
	{"ruo",		sizeof(PY_mb_ruo)/2,		PY_mb_ruo},
};

//s
PinYinDef const PYRankTwoList_s[]=
{
	{"sa",		sizeof(PY_mb_sa)/2,		PY_mb_sa},
	{"sai",		sizeof(PY_mb_sai)/2,		PY_mb_sai},
	{"san",		sizeof(PY_mb_san)/2,		PY_mb_san},
	{"sang",		sizeof(PY_mb_sang)/2,	PY_mb_sang},
	{"sao",		sizeof(PY_mb_sao)/2,		PY_mb_sao},
	{"se",		sizeof(PY_mb_se)/2,		PY_mb_se},	
	{"sen",		sizeof(PY_mb_sen)/2,		PY_mb_sen},
	{"seng",		sizeof(PY_mb_seng)/2,	PY_mb_seng},
	{"sha",		sizeof(PY_mb_sha)/2,		PY_mb_sha},
	{"shai",		sizeof(PY_mb_shai)/2,	PY_mb_shai},
	{"shan",		sizeof(PY_mb_shan)/2,	PY_mb_shan},
	{"shang",	sizeof(PY_mb_shang)/2,	PY_mb_shang},
	{"shao",		sizeof(PY_mb_shao)/2,	PY_mb_shao},
	{"she",		sizeof(PY_mb_she)/2,		PY_mb_she},
	{"shei",		sizeof(PY_mb_shei)/2,	PY_mb_shei},
	{"shen",		sizeof(PY_mb_shen)/2,	PY_mb_shen},
	{"sheng",	sizeof(PY_mb_sheng)/2,	PY_mb_sheng},
	{"shi",		sizeof(PY_mb_shi)/2,		PY_mb_shi},
	{"shou",		sizeof(PY_mb_shou)/2,	PY_mb_shou},
	{"shu",		sizeof(PY_mb_shu)/2,		PY_mb_shu},
	{"shua",		sizeof(PY_mb_shua)/2,	PY_mb_shua},
	{"shuai",	sizeof(PY_mb_shuai)/2,	PY_mb_shuai},
	{"shuan",	sizeof(PY_mb_shuan)/2,	PY_mb_shuan},
	{"shuang",	sizeof(PY_mb_shuang)/2,PY_mb_shuang},
	{"shui",		sizeof(PY_mb_shui)/2,	PY_mb_shui},
	{"shun",		sizeof(PY_mb_shun)/2,	PY_mb_shun},
	{"shuo",		sizeof(PY_mb_shuo)/2,	PY_mb_shuo},
	{"si",		sizeof(PY_mb_si)/2,		PY_mb_si},
	{"song",		sizeof(PY_mb_song)/2,	PY_mb_song},
	{"sou",		sizeof(PY_mb_sou)/2,		PY_mb_sou},
	{"su",		sizeof(PY_mb_su)/2,		PY_mb_su},
	{"suan",		sizeof(PY_mb_suan)/2,	PY_mb_suan},
	{"sui",		sizeof(PY_mb_sui)/2,		PY_mb_sui},
	{"sun",		sizeof(PY_mb_sun)/2,		PY_mb_sun},
	{"suo",		sizeof(PY_mb_suo)/2,		PY_mb_suo},
};

//t
PinYinDef const PYRankTwoList_t[]=
{
	{"ta",		sizeof(PY_mb_ta)/2,		PY_mb_ta},	
	{"tai",		sizeof(PY_mb_tai)/2,		PY_mb_tai},
	{"tan",		sizeof(PY_mb_tan)/2,		PY_mb_tan},
	{"tang",		sizeof(PY_mb_tang)/2,	PY_mb_tang},
	{"tao",		sizeof(PY_mb_tao)/2,		PY_mb_tao},
	{"te",		sizeof(PY_mb_te)/2,		PY_mb_te},
	{"teng",		sizeof(PY_mb_teng)/2,	PY_mb_teng},
	{"ti",		sizeof(PY_mb_ti)/2,		PY_mb_ti},
	{"tian",		sizeof(PY_mb_tian)/2,		PY_mb_tian},
	{"tiao",		sizeof(PY_mb_tiao)/2,		PY_mb_tiao},	
	{"tie",		sizeof(PY_mb_tie)/2,		PY_mb_tie},
	{"ting",		sizeof(PY_mb_ting)/2,	PY_mb_ting},
	{"tong",		sizeof(PY_mb_tong)/2,	PY_mb_tong},
	{"tou",		sizeof(PY_mb_tou)/2,		PY_mb_tou},
	{"tu",		sizeof(PY_mb_tu)/2,		PY_mb_tu},
	{"tuan",		sizeof(PY_mb_tuan)/2,	PY_mb_tuan},
	{"tui",		sizeof(PY_mb_tui)/2,		PY_mb_tui},
	{"tun",		sizeof(PY_mb_tun)/2,		PY_mb_tun},
	{"tuo",		sizeof(PY_mb_tuo)/2,		PY_mb_tuo},
};

//u
PinYinDef PYRankTwoList_u[]={" ",sizeof(PY_mb_space)/2,PY_mb_space};

//v
PinYinDef PYRankTwoList_v[]={" ",sizeof(PY_mb_space)/2,PY_mb_space};

//w
PinYinDef const PYRankTwoList_w[]=
{
	{"wa",		sizeof(PY_mb_wa)/2,		PY_mb_wa},		
	{"wai",		sizeof(PY_mb_wai)/2,		PY_mb_wai},	
	{"wan",		sizeof(PY_mb_wan)/2,	PY_mb_wan},	
	{"wang",	sizeof(PY_mb_wang)/2,	PY_mb_wang},	
	{"wei",		sizeof(PY_mb_wei)/2,		PY_mb_wei},	
	{"wen",		sizeof(PY_mb_wen)/2,	PY_mb_wen},	
	{"weng",	sizeof(PY_mb_weng)/2,	PY_mb_weng},	
	{"wo",		sizeof(PY_mb_wo)/2,		PY_mb_wo},	
	{"wu",		sizeof(PY_mb_wu)/2,		PY_mb_wu},	
};

//x
PinYinDef const PYRankTwoList_x[]=
{
	{"PY_mb_xi",		sizeof(PY_mb_xi)/2,		PY_mb_xi},	
	{"PY_mb_xia",		sizeof(PY_mb_xia)/2,		PY_mb_xia},
	{"PY_mb_xian",		sizeof(PY_mb_xian)/2,	PY_mb_xian},	
	{"PY_mb_xiang",		sizeof(PY_mb_xiang)/2,	PY_mb_xiang},
	{"PY_mb_xiao",		sizeof(PY_mb_xiao)/2,	PY_mb_xiao},
	{"PY_mb_xie",		sizeof(PY_mb_xie)/2,		PY_mb_xie},
	{"PY_mb_xin",		sizeof(PY_mb_xin)/2,		PY_mb_xin},	
	{"PY_mb_xing",		sizeof(PY_mb_xing)/2,	PY_mb_xing},
	{"PY_mb_xiong",		sizeof(PY_mb_xiong)/2,	PY_mb_xiong},
	{"PY_mb_xiu",		sizeof(PY_mb_xiu)/2,		PY_mb_xiu},	
	{"PY_mb_xu",		sizeof(PY_mb_xu)/2,		PY_mb_xu},
	{"PY_mb_xuan",		sizeof(PY_mb_xuan)/2,	PY_mb_xuan},	
	{"PY_mb_xue",		sizeof(PY_mb_xue)/2,		PY_mb_xue},	
	{"PY_mb_xun",		sizeof(PY_mb_xun)/2,		PY_mb_xun}
};

//y
PinYinDef const PYRankTwoList_y[]=
{
	{"ya",		sizeof(PY_mb_ya)/2,		PY_mb_ya},		
	{"yan",		sizeof(PY_mb_yan)/2,		PY_mb_yan},	
	{"yang",		sizeof(PY_mb_yang)/2,	PY_mb_yang},	
	{"yao",		sizeof(PY_mb_yao)/2,		PY_mb_yao},	
	{"ye",		sizeof(PY_mb_ye)/2,		PY_mb_ye},	
	{"yi",		sizeof(PY_mb_yi)/2,		PY_mb_yi},	
	{"yin",		sizeof(PY_mb_yin)/2,		PY_mb_yin},	
	{"ying",		sizeof(PY_mb_ying)/2,	PY_mb_ying},	
	{"yo",		sizeof(PY_mb_yo)/2,		PY_mb_yo},	
	{"yong",		sizeof(PY_mb_yong)/2,	PY_mb_yong},	
	{"you",		sizeof(PY_mb_you)/2,		PY_mb_you},		
	{"yu",		sizeof(PY_mb_yu)/2,		PY_mb_yu},	
	{"yuan",		sizeof(PY_mb_yuan)/2,	PY_mb_yuan},	
	{"yue",		sizeof(PY_mb_yue)/2,		PY_mb_yue},	
	{"yun",		sizeof(PY_mb_yun)/2,		PY_mb_yun},	
};

//z
PinYinDef const PYRankTwoList_z[]=
{
	{"za",		sizeof(PY_mb_za)/2,		PY_mb_za},	
	{"zai",		sizeof(PY_mb_zai)/2,		PY_mb_zai},
	{"zan",		sizeof(PY_mb_zan)/2,		PY_mb_zan},
	{"zang",		sizeof(PY_mb_zang)/2,	PY_mb_zang},
	{"zao",		sizeof(PY_mb_zao)/2,		PY_mb_zao},
	{"ze",		sizeof(PY_mb_ze)/2,		PY_mb_ze},
	{"zei",		sizeof(PY_mb_zei)/2,		PY_mb_zei},
	{"zen",		sizeof(PY_mb_zen)/2,		PY_mb_zen},
	{"zeng",		sizeof(PY_mb_zeng)/2,	PY_mb_zeng},
	{"zha",		sizeof(PY_mb_zha)/2,		PY_mb_zha},
	{"zhai",		sizeof(PY_mb_zhai)/2,	PY_mb_zhai},
	{"zhan",		sizeof(PY_mb_zhan)/2,	PY_mb_zhan},
	{"zhang",	sizeof(PY_mb_zhang)/2,	PY_mb_zhang},
	{"zhao",		sizeof(PY_mb_zhao)/2,	PY_mb_zhao},
	{"zhe",		sizeof(PY_mb_zhe)/2,		PY_mb_zhe},
	{"zhen",		sizeof(PY_mb_zhen)/2,	PY_mb_zhen},
	{"zheng",	sizeof(PY_mb_zheng)/2,	PY_mb_zheng},
	{"zhi",		sizeof(PY_mb_zhi)/2,		PY_mb_zhi},
	{"zhong",	sizeof(PY_mb_zhong)/2,	PY_mb_zhong},
	{"zhou",		sizeof(PY_mb_zhou)/2,	PY_mb_zhou},
	{"zhu",		sizeof(PY_mb_zhu)/2,		PY_mb_zhu},	
	{"zhua",		sizeof(PY_mb_zhua)/2,	PY_mb_zhua},
	{"zhuai",	sizeof(PY_mb_zhuai)/2,	PY_mb_zhuai},
	{"zhuan",	sizeof(PY_mb_zhuan)/2,	PY_mb_zhuan},
	{"zhuang",	sizeof(PY_mb_zhuang)/2,PY_mb_zhuang},
	{"zhui",		sizeof(PY_mb_zhui)/2,	PY_mb_zhui},
	{"zhun",		sizeof(PY_mb_zhun)/2,	PY_mb_zhun},
	{"zhuo",		sizeof(PY_mb_zhuo)/2,	PY_mb_zhuo},
	{"zi",		sizeof(PY_mb_zi)/2,		PY_mb_zi},
	{"zong",		sizeof(PY_mb_zong)/2,	PY_mb_zong},
	{"zou",		sizeof(PY_mb_zou)/2,		PY_mb_zou},	
	{"zu",		sizeof(PY_mb_zu)/2,		PY_mb_zu},
	{"zuan",		sizeof(PY_mb_zuan)/2,	PY_mb_zuan},
	{"zui",		sizeof(PY_mb_zui)/2,		PY_mb_zui},
	{"zun",		sizeof(PY_mb_zun)/2,		PY_mb_zun},
	{"zuo",		sizeof(PY_mb_zuo)/2,		PY_mb_zuo},
};



PinYinDef const PYRankTwoList_end[]={"",1,PY_mb_space};
#endif
