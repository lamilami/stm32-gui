#include "chinese_pinyin.h"

//�������б�
const unsigned char PY_mb_space     []={""};
const unsigned char PY_mb_a     []={"����߹�����"};
const unsigned char PY_mb_ai    []={"�������������������������������������������"};
const unsigned char PY_mb_an    []={"�����������������ϰ����������������"};
const unsigned char PY_mb_ang   []={"�������a"};
const unsigned char PY_mb_ao    []={"�������������°ð���������������������������"};
const unsigned char PY_mb_ba    []={"�˰ͰְΰŰưǰȰɰʰ̰ϰаѰҰӰ԰���������������"};
const unsigned char PY_mb_bai   []={"�װذٰڰ۰ܰݰ޲�����"};
const unsigned char PY_mb_ban   []={"���߰������������������������"};
const unsigned char PY_mb_bang  []={"���������������������"};
const unsigned char PY_mb_bao   []={"�����������������������������������������������������"};
const unsigned char PY_mb_bei   []={"���������������������������������������������������������"};;
const unsigned char PY_mb_ben   []={"���������������"};
const unsigned char PY_mb_beng  []={"�������±ñı�ܡ���"};
const unsigned char PY_mb_bi    []={"�ƱǱȱɱʱ˱̱ͱαϱбѱұӱԱ�ذ�ֱױرٱڱ۱ܱ�������������ݩ��޵�������������������������������������������"};
const unsigned char PY_mb_bian  []={"�߱�����ޱ�������������������������������"};
const unsigned char PY_mb_biao  []={"�����������������������"};
const unsigned char PY_mb_bie   []={"�������"};
const unsigned char PY_mb_bin   []={"������������������������������"};
const unsigned char PY_mb_bing  []={"������������������������������"};
const unsigned char PY_mb_bo    []={"�ذٰ�����������������������������������������������ެ�������������������"};
const unsigned char PY_mb_bu    []={"��������������������������߲�����������"};
const unsigned char PY_mb_ca    []={"������"};
const unsigned char PY_mb_cai   []={"�ŲƲǲ²òĲȲɲʲ˲�"};
const unsigned char PY_mb_can   []={"�ͲβϲвѲҲ����������"};
const unsigned char PY_mb_cang  []={"�Բղֲײ���"};
const unsigned char PY_mb_cao   []={"�ݲٲڲ۲�ܳ�������"};
const unsigned char PY_mb_ce    []={"����޲���"};
const unsigned char PY_mb_cen   []={" ����"};
const unsigned char PY_mb_ceng  []={"�������"};
const unsigned char PY_mb_cha   []={"������������ɲ���������������������"};
const unsigned char PY_mb_chai  []={"�����٭�������"};
const unsigned char PY_mb_chan  []={"���������������������������������������������"};
const unsigned char PY_mb_chang []={"�������������������������������������������������"};
const unsigned char PY_mb_chao  []={"�������������������½�������"};
const unsigned char PY_mb_che   []={"�����������������"};
const unsigned char PY_mb_chen  []={"���������������³óĳ����������������"};
const unsigned char PY_mb_cheng []={"�ųƳǳȳɳʳ˳̳ͳγϳгѳҳ�ʢة�����������������������"};
const unsigned char PY_mb_chi   []={"�Գճֳ׳سٳڳ۳ܳݳ޳߳������߳������ܯ����������������������������"};
const unsigned char PY_mb_chong []={"����������������������"};
const unsigned char PY_mb_chou  []={"�������������ٱ������"};
const unsigned char PY_mb_chu   []={"����������������������������������ءۻ�������������������"};
const unsigned char PY_mb_chuai []={"����������"};
const unsigned char PY_mb_chuan []={"������������������������"};
const unsigned char PY_mb_chuang[]={"����������������"};
const unsigned char PY_mb_chui  []={"��������������"};
const unsigned char PY_mb_chun  []={"��������������ݻ����"};
const unsigned char PY_mb_chuo  []={"������������"};
const unsigned char PY_mb_ci    []={"�˴̴ʹ��Ų�ôĴŴƴǴȴɴ���������������"};
const unsigned char PY_mb_cong  []={"�ӴԴϴдѴ������������"};
const unsigned char PY_mb_cou   []={"������"};
const unsigned char PY_mb_cu    []={"�ִ״ش��������������"};
const unsigned char PY_mb_cuan  []={"�ڴ۴�����ߥ����"};
const unsigned char PY_mb_cui   []={"�ݴ޴ߴ����������������"};
const unsigned char PY_mb_cun   []={"��������"};
const unsigned char PY_mb_cuo   []={"��������������������������"};
const unsigned char PY_mb_da    []={"��������������������������"};
const unsigned char PY_mb_dai   []={"���������������������������ܤ߰߾��������"};
const unsigned char PY_mb_dan   []={"��������������������������������ʯ��������������������"};
const unsigned char PY_mb_dang  []={"����������������������"};
const unsigned char PY_mb_dao   []={"��������������������������߶���������"};
const unsigned char PY_mb_de    []={"�µõĵ��"};
const unsigned char PY_mb_dei   []={"��"};
const unsigned char PY_mb_deng  []={"�εŵƵǵȵɵʵ������������"};
const unsigned char PY_mb_di    []={"�ĵֵ׵صٵڵ۵ܵݵ̵͵εϵеѵҵӵԵյ���ص��ڮ��ۡ��ݶ��������������������"};
const unsigned char PY_mb_dia   []={"��"};
const unsigned char PY_mb_dian  []={"����������ߵ����������������������"};
const unsigned char PY_mb_diao  []={"���������������������"};
const unsigned char PY_mb_die   []={"����������������ܦ�����������"};
const unsigned char PY_mb_ding  []={"������������������������������������"};
const unsigned char PY_mb_diu   []={"����"};
const unsigned char PY_mb_dong  []={"��������������������������������"};
const unsigned char PY_mb_dou   []={"����������������������"};
const unsigned char PY_mb_du    []={"�Ƕȶɶ������������¶öĶŶƶ�ܶ�������������"};
const unsigned char PY_mb_duan  []={"�˶̶Ͷζ϶������"};
const unsigned char PY_mb_dui   []={"�ѶҶӶ�����"};
const unsigned char PY_mb_dun   []={"�ܶնֶ׶ضٶڶ۶��������������"};
const unsigned char PY_mb_duo   []={"���ȶ޶߶�����������������������"};
const unsigned char PY_mb_e     []={"������������������Ŷج������ݭ��������������������"};
const unsigned char PY_mb_ei    []={"��"};
const unsigned char PY_mb_en    []={"������"};
const unsigned char PY_mb_er    []={"�������������������������"};
const unsigned char PY_mb_fa    []={"��������������������"};
const unsigned char PY_mb_fan   []={"����������������������������������ެ����������"};
const unsigned char PY_mb_fang  []={"���������������·÷ķ�������������"};
const unsigned char PY_mb_fei   []={"�ƷǷȷɷʷ˷̷ͷηϷз�����������������������������������"};
const unsigned char PY_mb_fen   []={"�ַҷܷݷ޷߷�ӷԷշ׷طٷڷ��������������"};
const unsigned char PY_mb_feng  []={"����������������ٺۺ�������"};
const unsigned char PY_mb_fo    []={"��"};
const unsigned char PY_mb_fou   []={"���"};
const unsigned char PY_mb_fu    []={"���𸵸�����������������������������������������������������������������������������������������ۮܽ������ݳ����߻����������������������������������������������"};
const unsigned char PY_mb_ga    []={"���¼п�٤���������"};
const unsigned char PY_mb_gai   []={"�øĸŸƸǸȽ�ؤ���������"};
const unsigned char PY_mb_gan   []={"�ɸʸ˸̸͸θϸиѸҸ�������ߦ���������������"};
const unsigned char PY_mb_gang  []={"�Ըոָ׸ظٸڸ۸ܿ�����"};
const unsigned char PY_mb_gao   []={"��޸߸�ݸ�����غھ۬޻��������"};
const unsigned char PY_mb_ge    []={"�����Ǹ����������������������Ͽ�ت������ܪ��������������"};
const unsigned char PY_mb_gei   []={"��"};
const unsigned char PY_mb_gen   []={"����بݢ����"};
const unsigned char PY_mb_geng  []={"�����������������������"};
const unsigned char PY_mb_gong  []={"���������������������������������������"};
const unsigned char PY_mb_gou   []={"������������������ڸ��������������������"};
const unsigned char PY_mb_gu    []={"�������������¹ùĹŹƹǹȹɹʹ˹̹ͼ���ڬ��������������������������������������"};
const unsigned char PY_mb_gua   []={"�ιϹйѹҹ���ڴ�������"};
const unsigned char PY_mb_guai  []={"�Թչ���"};
const unsigned char PY_mb_guan  []={"�عٹڹ۹ܹݹ޹߹������ݸ������������"};
const unsigned char PY_mb_guang []={"������������"};
const unsigned char PY_mb_gui   []={"������������������Ȳ���������������������"};
const unsigned char PY_mb_gun   []={"�������������"};
const unsigned char PY_mb_guo   []={"������������������������������������"};
const unsigned char PY_mb_ha    []={"������"};
const unsigned char PY_mb_hai   []={"���Ⱥ�������������������"};
const unsigned char PY_mb_han   []={"��������������������������������������������������������"};
const unsigned char PY_mb_hang  []={"�к��������������"};
const unsigned char PY_mb_hao   []={"�ºúĺ������尸亾��������޶�������"};
const unsigned char PY_mb_he    []={"�ǺȺɺʺ˺̺ͺκϺӺкѺҺԺպغֺ���ڭ�������������������"};
const unsigned char PY_mb_hei   []={"�ں�"};
const unsigned char PY_mb_hen   []={"�ۺܺݺ�"};
const unsigned char PY_mb_heng  []={"�ߺ����޿����"};
const unsigned char PY_mb_hong  []={"��������������ڧݦޮް����"};
const unsigned char PY_mb_hou   []={"��������ܩ��������������"};
const unsigned char PY_mb_hu    []={"���������˺��������������������������������������������������������������������������"};
const unsigned char PY_mb_hua   []={"�������������������������"};
const unsigned char PY_mb_huai  []={"������������"};
const unsigned char PY_mb_huan  []={"�����������������������»���佻�ۨۼ����ߧ���������������"};
const unsigned char PY_mb_huang []={"�λĻŻƻǻȻɻʻ˻̻ͻϻл��������������������"};
const unsigned char PY_mb_hui   []={"��ػٻڻһӻԻջֻ׻ۻܻݻ޻߻����������ڶ����ޥ��������������������"};
const unsigned char PY_mb_hun   []={"�������ڻ��������"};
const unsigned char PY_mb_huo   []={"�ͻ��������������޽߫������������"};
const unsigned char PY_mb_ji    []={"�ƼǸ��������������������������������������ȼɼʼ����������������������������������������������¼üļż˼̼ͽ���ϵآؽ����٥����ܸ����ݽ��ު��ߴ�����������������������������������������������������������"};
const unsigned char PY_mb_jia   []={"�ҼӼμмѼԼռּ׼ؼټڼۼܼݼ޼�����٤ۣ��������������������������������"};
const unsigned char PY_mb_jian  []={"�������򽡼��߼����������������������������������������������������������������������������������������������������"};
const unsigned char PY_mb_jiang []={"���罩����������������������ǿ����������������"};
const unsigned char PY_mb_jiao  []={"�нϾ���У�������������������������½ýĽŽƽȽɽʽ˽̽ͽν�ٮ��ܴ����������������������"};
const unsigned char PY_mb_jie   []={"������ҽܽӽԽ���ݽ޽սֽ׽ؽٽڽ۽߽�������ڦڵ�������������������������"};
const unsigned char PY_mb_jin   []={"�����������������������������������ݣ������������������������"};
const unsigned char PY_mb_jing  []={"������������������������������������������������������������ݼ������������������"};
const unsigned char PY_mb_jiong []={"����������"};
const unsigned char PY_mb_jiu   []={"�ž;Ⱦ��������¾þľƾɾʾ˾̾ξ�����������������"};
const unsigned char PY_mb_ju    []={"�޾߾���峵���ӾԾվ־׾ؾپھ۾ܾݾ���ϾоѾ���ڪ��������������������������������������������"};
const unsigned char PY_mb_juan  []={"��������Ȧ۲�������������"};
const unsigned char PY_mb_jue   []={"���������Ǿ����ž������������ܥާ���������������������"};
const unsigned char PY_mb_jun   []={"��������������������������������"};
const unsigned char PY_mb_ka    []={"��������������"};
const unsigned char PY_mb_kai   []={"�������������������������"};
const unsigned char PY_mb_kan   []={"������������٩�����ݨ�ۼ��"};
const unsigned char PY_mb_kang  []={"��������������������"};
const unsigned char PY_mb_kao   []={"����������������"};
const unsigned char PY_mb_ke    []={"�ɿʿ˿ƿ̿Ϳ�྿����¿ÿĿſǿ���������������������������������"};
const unsigned char PY_mb_ken   []={"�Ͽпѿ���"};
const unsigned char PY_mb_keng  []={"�ӿ������"};
const unsigned char PY_mb_kong  []={"�տֿ׿�������"};
const unsigned char PY_mb_kou   []={"�ٿڿۿ���ޢߵ����"};
const unsigned char PY_mb_ku    []={"�ݿ޿߿���������ܥ�"};
const unsigned char PY_mb_kua   []={"������٨�"};
const unsigned char PY_mb_kuai  []={"��������ۦ������"};
const unsigned char PY_mb_kuan  []={"�����"};
const unsigned char PY_mb_kuang []={"�����������ڲڿ������������"};
const unsigned char PY_mb_kui   []={"����������������������ظ���������������������������"};
const unsigned char PY_mb_kun   []={"��������������������"};
const unsigned char PY_mb_kuo   []={"����������"};
const unsigned char PY_mb_la    []={"�������������������������"};
const unsigned char PY_mb_lai   []={"���������������������"};
const unsigned char PY_mb_lan   []={"����������������������������������������"};
const unsigned char PY_mb_lang  []={"������������������������ݹ"};
const unsigned char PY_mb_lao   []={"�������������������������������������"};
const unsigned char PY_mb_le    []={"��������߷����"};
const unsigned char PY_mb_lei   []={"��������������������������ڳ������������"};
const unsigned char PY_mb_leng  []={"������ܨ�"};
const unsigned char PY_mb_li    []={"��������������������������������������������������������������������تٳٵ۪����ݰ��޼߿�����������������������������������������������������������"};
const unsigned char PY_mb_lia   []={"��"};
const unsigned char PY_mb_lian  []={"������������������������������������������������"};
const unsigned char PY_mb_liang []={"������������������������ܮݹ�����"};
const unsigned char PY_mb_liao  []={"��������������������������ޤ������������"};
const unsigned char PY_mb_lie   []={"�������������������������"};
const unsigned char PY_mb_lin   []={"�����������������������������������������������"};
const unsigned char PY_mb_ling  []={"��������������������������������۹��������������������"};
const unsigned char PY_mb_liu   []={"����������������������µ½����������������"};
const unsigned char PY_mb_lo    []={"��"}; 
const unsigned char PY_mb_long  []={"��Ū��������¡¢£¤���������������"};
const unsigned char PY_mb_lou   []={"¥¦§¨©ª¶�����������������"};
const unsigned char PY_mb_lu    []={"��«¬­®¯°±²³´µ¶·¸¹º»¼½¾����ߣ������������������������������������"};
const unsigned char PY_mb_lv    []={"��������������������������¿�������������"}; 
const unsigned char PY_mb_luan  []={"������������"};
const unsigned char PY_mb_lue   []={"�����"};
const unsigned char PY_mb_lun   []={"����������������"};
const unsigned char PY_mb_luo   []={"���޸����������������������������������������������������"};
const unsigned char PY_mb_m     []={"߼"};  
const unsigned char PY_mb_ma    []={"������������������ĦĨ��������"};
const unsigned char PY_mb_mai   []={"������������������áܬ��������������"};
const unsigned char PY_mb_man   []={"����������á������"};
const unsigned char PY_mb_mang  []={"âãäåæç��������"};
const unsigned char PY_mb_mao   []={"èéêëì��îïðñòó��í�����������������"};
const unsigned char PY_mb_me    []={"ô"};
const unsigned char PY_mb_mei   []={"ÿ����õö��������÷øùúûüýþ��ݮ�����������"};
const unsigned char PY_mb_men   []={"�������������"};
const unsigned char PY_mb_meng  []={"��������������������ޫ��������������"};
const unsigned char PY_mb_mi    []={"����������������������������������ڢ������������������������"};
const unsigned char PY_mb_mian  []={"�����������������������������"};
const unsigned char PY_mb_miao  []={"������������������������������"};
const unsigned char PY_mb_mie   []={"����ؿ�����"};
const unsigned char PY_mb_min   []={"������������������������������"};
const unsigned char PY_mb_ming  []={"������������ڤ���������"};
const unsigned char PY_mb_miu   []={"����"};
const unsigned char PY_mb_mo    []={"��û��ġĢģĤĥĦħĨĩĪīĬĭĮįİ���������������������������"};
const unsigned char PY_mb_mou   []={"ıĲĳٰ����������"};
const unsigned char PY_mb_mu    []={"ľĿ��ģĲĴĵĶķĸĹĺĻļĽ���������������"};
const unsigned char PY_mb_na    []={"����������������������"};
const unsigned char PY_mb_nai   []={"����������ؾ٦ܵ����"};
const unsigned char PY_mb_nan   []={"����������������"};
const unsigned char PY_mb_nang  []={"������߭��"};
const unsigned char PY_mb_nao   []={"����������ث������������"};
const unsigned char PY_mb_ne    []={"����ګ"};
const unsigned char PY_mb_nei   []={"����"};
const unsigned char PY_mb_nen   []={"���"};
const unsigned char PY_mb_neng  []={"��"};
const unsigned char PY_mb_ng    []={"��"}; 
const unsigned char PY_mb_ni    []={"������������������������٣�����������������"};
const unsigned char PY_mb_nian  []={"��������������إ���������"};
const unsigned char PY_mb_niang []={"����"};
const unsigned char PY_mb_niao  []={"������������"};
const unsigned char PY_mb_nie   []={"�������������������ؿ�����"};
const unsigned char PY_mb_nin   []={"��"};
const unsigned char PY_mb_ning  []={"��������šŢ�������"};
const unsigned char PY_mb_niu   []={"ţŤťŦ�������"};
const unsigned char PY_mb_nong  []={"ŧŨũŪٯ��"};
const unsigned char PY_mb_nou   []={"��"};
const unsigned char PY_mb_nu    []={"ūŬŭ��������"};
const unsigned char PY_mb_nuan  []={"ů"};
const unsigned char PY_mb_nue   []={"űŰ"};
const unsigned char PY_mb_nuo   []={"��ŲųŴŵ�������"};
const unsigned char PY_mb_nv    []={"Ů�����"};
const unsigned char PY_mb_o     []={"Ŷ���"};
const unsigned char PY_mb_ou    []={"ŷŸŹźŻżŽ��ک�����"};
const unsigned char PY_mb_pa    []={"�ǰ�žſ��������������"};
const unsigned char PY_mb_pai   []={"��������������ٽ����"};
const unsigned char PY_mb_pan   []={"�������������������������������������"};
const unsigned char PY_mb_pang  []={"����������������������"};
const unsigned char PY_mb_pao   []={"������������������������"};
const unsigned char PY_mb_pei   []={"�����������������������������"};
const unsigned char PY_mb_pen   []={"������"};
const unsigned char PY_mb_peng  []={"������������������������������ܡ���"};
const unsigned char PY_mb_pi    []={"�ٷ�����������������ơƢƣƤƥƦƧاƨƩ�����������ۯ����ܱ��ߨ�����������������������"};
const unsigned char PY_mb_pian  []={"���ƪƫƬƭ��������������"};
const unsigned char PY_mb_piao  []={"ƮƯưƱ����������������"};
const unsigned char PY_mb_pie   []={"ƲƳد���"};
const unsigned char PY_mb_pin   []={"ƴƵƶƷƸ�������"};
const unsigned char PY_mb_ping  []={"��ƹƺƻƼƽƾƿ����ٷ�����"};
const unsigned char PY_mb_po    []={"��������������������������۶�����������"};
const unsigned char PY_mb_pou   []={"������"};
const unsigned char PY_mb_pu    []={"�ձ������������������������������������������������"};
const unsigned char PY_mb_qi    []={"����������������������������������������������������������������������������������ؽ�����������ٹ��ܻ��������������ޭ����������������������"};
const unsigned char PY_mb_qia   []={"����ǡǢ������"};
const unsigned char PY_mb_qian  []={"ǣǤǥǦǧǨǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸ��ٻ����ܷ����ݡ������������������������"};
const unsigned char PY_mb_qiang []={"ǹǺǻǼǽǾǿ�������������������������"};
const unsigned char PY_mb_qiao  []={"��������������������������������ȸڽ��������������������"};
const unsigned char PY_mb_qie   []={"����������٤�����ۧ������"};
const unsigned char PY_mb_qin   []={"��������������������������������������������"};
const unsigned char PY_mb_qing  []={"���������������������������������������������������"};
const unsigned char PY_mb_qiong []={"�����������������"};
const unsigned char PY_mb_qiu   []={"�������������������ٴ������������������������"};
const unsigned char PY_mb_qu    []={"����������������ȡȢȣȤȥ������ڰ۾����ޡ޾����������������������"};
const unsigned char PY_mb_quan  []={"ȦȧȨȩȪȫȬȭȮȯȰڹ�����������������"};
const unsigned char PY_mb_que   []={"ȱȲȳȴȵȶȷȸ�����"};
const unsigned char PY_mb_qun   []={"ȹȺ����"};
const unsigned char PY_mb_ran   []={"ȻȼȽȾ������"};
const unsigned char PY_mb_rang  []={"ȿ�����������"};
const unsigned char PY_mb_rao   []={"�����������"};
const unsigned char PY_mb_re    []={"������"};
const unsigned char PY_mb_ren   []={"�����������������������������������"};
const unsigned char PY_mb_reng  []={"����"};
const unsigned char PY_mb_ri    []={"��"};
const unsigned char PY_mb_rong  []={"������������������������������"};
const unsigned char PY_mb_rou   []={"������������"};
const unsigned char PY_mb_ru    []={"���������������������������޸�������"};
const unsigned char PY_mb_ruan  []={"������"};
const unsigned char PY_mb_rui   []={"�����������ި�"};
const unsigned char PY_mb_run   []={"����"};
const unsigned char PY_mb_ruo   []={"����ټ��"};
const unsigned char PY_mb_sa    []={"������ئ�����"};
const unsigned char PY_mb_sai   []={"����������"};
const unsigned char PY_mb_san   []={"����ɡɢ�����"};
const unsigned char PY_mb_sang  []={"ɣɤɥ�����"};
const unsigned char PY_mb_sao   []={"ɦɧɨɩ����ܣ����"};
const unsigned char PY_mb_se    []={"��ɪɫɬ����"};
const unsigned char PY_mb_sen   []={"ɭ"};
const unsigned char PY_mb_seng  []={"ɮ"};
const unsigned char PY_mb_sha   []={"ɯɰɱɲɳɴɵɶɷɼ��������������"};
const unsigned char PY_mb_shai  []={"ɫɸɹ"};
const unsigned char PY_mb_shan  []={"����ɺɻɼɽɾɿ��������������������դڨ�����������۷���������������������"};
const unsigned char PY_mb_shang []={"�������������������������"};
const unsigned char PY_mb_shao  []={"������������������������ۿ�����������"};
const unsigned char PY_mb_she   []={"�����������������������������������������"};
const unsigned char PY_mb_shei  []={"˭"}; 
const unsigned char PY_mb_shen  []={"����������������������������������ʲڷ��ݷ�������������"};
const unsigned char PY_mb_sheng []={"��������������ʡʢʣʤʥ����������"};
const unsigned char PY_mb_shi   []={"��ʦʧʨʩʪʫʬʭʮʯʰʱʲʳʴʵʶʷʸʹʺʻʼʽʾʿ��������������������������������������������߱��ֳ������ݪ��������������������������"};
const unsigned char PY_mb_shou  []={"���������������������������"};
const unsigned char PY_mb_shu   []={"����������������������������������������������������������������ˡٿ�������ح���������������"};
const unsigned char PY_mb_shua  []={"ˢˣ�"};
const unsigned char PY_mb_shuai []={"��ˤ˥˦˧�"};
const unsigned char PY_mb_shuan []={"˨˩����"};
const unsigned char PY_mb_shuang[]={"˪˫ˬ����"};
const unsigned char PY_mb_shui  []={"ˮ˯˰˵��"};
const unsigned char PY_mb_shun  []={"˱˲˳˴"};
const unsigned char PY_mb_shuo  []={"��˵˶˷˸����������"};
const unsigned char PY_mb_si    []={"˹˺˻˼˽˾˿����������������������ٹ���������������������������"};
const unsigned char PY_mb_song  []={"��������������������������ݿڡ"};
const unsigned char PY_mb_sou   []={"�����������������������޴"};
const unsigned char PY_mb_su    []={"�����������������������������������������"};
const unsigned char PY_mb_suan  []={"�������"};
const unsigned char PY_mb_sui   []={"����������������������"};
const unsigned char PY_mb_sun   []={"������"};
const unsigned char PY_mb_suo   []={"�����������������������ɯ��������"};
const unsigned char PY_mb_ta    []={"����������̡̢�̣̤�����������������"};
const unsigned char PY_mb_tai   []={"̧̨̥̦̩̪̫̬̭��ۢ޷����������"};
const unsigned char PY_mb_tan   []={"��̴̵̶̷̸̮̯̰̱̲̳̹̺̻̼̽̾̿��۰������������"};
const unsigned char PY_mb_tang  []={"�������������������������������������������������"};
const unsigned char PY_mb_tao   []={"����������������������߶��������ػ"};
const unsigned char PY_mb_te    []={"��߯���"};
const unsigned char PY_mb_teng  []={"����������"};
const unsigned char PY_mb_ti    []={"���������������������������������������������"};
const unsigned char PY_mb_tian  []={"����������������������������"};
const unsigned char PY_mb_tiao  []={"������������٬������������������"};
const unsigned char PY_mb_tie   []={"�����������"};
const unsigned char PY_mb_ting  []={"������ͣͤͥͦͧ͢͡��������������"};
const unsigned char PY_mb_tong  []={"ͩͫͬͭͮͯͰͱͲͳʹ١��������ͪ���������"};
const unsigned char PY_mb_tou   []={"͵Ͷͷ͸������"};
const unsigned char PY_mb_tu    []={"͹ͺͻͼͽ;Ϳ��������ܢݱ������"};
const unsigned char PY_mb_tuan  []={"���������"};
const unsigned char PY_mb_tui   []={"��������������"};
const unsigned char PY_mb_tun   []={"�����������������"};
const unsigned char PY_mb_tuo   []={"˵������������������������ر٢����������������������"};
const unsigned char PY_mb_wa    []={"�������������������"};
const unsigned char PY_mb_wai   []={"������"};
const unsigned char PY_mb_wan   []={"��������������������������������������ܹݸ��������������"};
const unsigned char PY_mb_wang  []={"�����������������������������"};
const unsigned char PY_mb_wei   []={"Ϊλν��Ρ΢ΣΤάΥΦΧΨΩΫέήίΰαβγδεζηθικμξο������������ޱ�����������������������������������"};
const unsigned char PY_mb_wen   []={"�������������������������������"};
const unsigned char PY_mb_weng  []={"��������޳"};
const unsigned char PY_mb_wo    []={"��������������������ݫ���������"};
const unsigned char PY_mb_wu    []={"�����������������������أ����������������������������������������������������������������������������������"};
const unsigned char PY_mb_xi    []={"ϣϰϦϷϸ����������������������ϡ��ϢϤϥϧϨϪϫϬϮϯϱϲϴϵ϶���������������ϭϩϳ��������ۭݾ���������������������������������������������"};
const unsigned char PY_mb_xia   []={"ϹϺϻϼϽϾϿ���������������������������"};
const unsigned char PY_mb_xian  []={"ϳϴ��������������������������������������������������������ݲ޺������������������������������"};
const unsigned char PY_mb_xiang []={"������������������������������������������ܼ������������"};
const unsigned char PY_mb_xiao  []={"С��Ф��������������������ТУХЦЧ���������������������"};
const unsigned char PY_mb_xie   []={"ЩЪЫЬЭЮЯабвгдежзийклмѪ��ШҶ��������ޯߢ���������������������"};
const unsigned char PY_mb_xin   []={"ноп��������������ܰݷ����ض����"};
const unsigned char PY_mb_xing  []={"��ʡ�����������������������������������ߩ���"};
const unsigned char PY_mb_xiong []={"��������������ܺ"};
const unsigned char PY_mb_xiu   []={"������������������������������������"};
const unsigned char PY_mb_xu    []={"��������������������������������������ڼ������ޣ������������������"};
const unsigned char PY_mb_xuan  []={"��ѡ��������������Ѥ��ѣѢ����������������������ȯ"};
const unsigned char PY_mb_xue   []={"��ѥѦѧѨѩѪ���������"};
const unsigned char PY_mb_xun   []={"ѰѮѸѶѯѵѫѬѭѱѲѳѴѷۨ����޹������࿣ݡަ����������"};
const unsigned char PY_mb_ya    []={"��ѿ����ѹ��ѺѻѼѽѾ����������������������������������"};
const unsigned char PY_mb_yan   []={"��������������������������������������������������������������������������������ٲ��Ǧ����������ڥ����۱۳ܾ�����������������������������"};
const unsigned char PY_mb_yang  []={"������������������������������������������������"};
const unsigned char PY_mb_yao   []={"Ҫ��ҧҩ����ҡҢ���ңҤҥҦҨҫԿزس��ߺ����ű�����������������������"};
const unsigned char PY_mb_ye    []={"ҲҳҵҶҹҺҬҭҮүҰұҴҷҸа��������������������"};
const unsigned char PY_mb_yi    []={"һ��������������������ҼҽҾҿ�������������������������������������������������������������������������β��������٫ڱ������ܲ����޲������߽߮�����������������������������������������������������������������"};
const unsigned char PY_mb_yin   []={"����ӡ����������������������������ط�۴����ܧ������������������"};
const unsigned char PY_mb_ying  []={"ӳӰӢӨөӪӫӣӤӥӦӧӬӭӮӯӱӲ��ݺ�����������۫�������������������"};
const unsigned char PY_mb_yo    []={"Ӵ���"};
const unsigned char PY_mb_yong  []={"��ӵӶ��ӿӷӸӹӺӻӼӽӾ����ٸ��ܭ�����������"};
const unsigned char PY_mb_you   []={"��������������������������������������������������������٧ݬݯݵ��������������������"};
const unsigned char PY_mb_yu    []={"������������������ԡ������������������������������������������������������������ԢԣԤԥԦ��ع�����εξخ��ٶ������������������������������������������������������������������������"};
const unsigned char PY_mb_yuan  []={"ԭԪ԰ԱԲԴԵԶԸԹԺԧԨԩԫԬԮԯԳԷ��ܫܾ������������������"};

//#ifndef WIN_SIM
const unsigned char PY_mb_yue   []={"��������˵ԻԼԽԾԿ����������������"};//
//#endif

//#ifdef WIN_SIM
//const unsigned char PY_mb_yue   []={"��������˵ԻԼԽԾԿ����������������"};
//#endif

const unsigned char PY_mb_yun   []={"��Ա�������������������������ܿ��۩����������"};
const unsigned char PY_mb_za    []={"��������զ����"};
const unsigned char PY_mb_zai   []={"������������������"};
const unsigned char PY_mb_zan   []={"���������������������"};
const unsigned char PY_mb_zang  []={"�����������"};
const unsigned char PY_mb_zao   []={"������������������������������"};
const unsigned char PY_mb_ze    []={"��������զ�����������������"};
const unsigned char PY_mb_zei   []={"��"};
const unsigned char PY_mb_zen   []={"����"};
const unsigned char PY_mb_zeng  []={"��������������"};
const unsigned char PY_mb_zha   []={"��բ����������ագդեզէըթ߸��������������������"};
const unsigned char PY_mb_zhai  []={"լխծ����ժիկ���"};
const unsigned char PY_mb_zhan  []={"ռսվչմ��հձղճյնշոպ��ջտ�������"};
const unsigned char PY_mb_zhang []={"�������������������������˳������������۵���"};
const unsigned char PY_mb_zhao  []={"����צ���׳�����گ������������������"};
const unsigned char PY_mb_zhe   []={"������������������������ߡ��������������"};
const unsigned char PY_mb_zhen  []={"��������������������������������֡����������������������������"};
const unsigned char PY_mb_zheng []={"��֤��������������������֢֣ں����������"};
const unsigned char PY_mb_zhi   []={"��������ֻ֧ʶִֵֹ��ּֽ֥֭֮־ְֱֲֳֶַָֺֿ֦֪֫֬֯��������������֨֩������������ش��ۤ������������������������������������������������������������"};
const unsigned char PY_mb_zhong []={"����������������������ڣ���������"};
const unsigned char PY_mb_zhou  []={"����������������������������ݧ����������������"};
const unsigned char PY_mb_zhu   []={"��סעף������������������������������������������פ������٪����ۥ��������������������������������ؼ"};
const unsigned char PY_mb_zhua  []={"ץצ��"};
const unsigned char PY_mb_zhuai []={"קת"};
const unsigned char PY_mb_zhuan []={"��רשת׫׬׭�������"};
const unsigned char PY_mb_zhuang[]={"��׮ׯװױײ׳״���"};
const unsigned char PY_mb_zhui  []={"׵׶׷׸׹׺�������"};
const unsigned char PY_mb_zhun  []={"׻׼����"};
const unsigned char PY_mb_zhuo  []={"��׽׾׿��������������پ��ߪ�����������"};
const unsigned char PY_mb_zi    []={"���������������������������������֨�������������������������������������"};
const unsigned char PY_mb_zong  []={"����������������������"};
const unsigned char PY_mb_zou   []={"������������۸����"};
const unsigned char PY_mb_zu    []={"����������������������"};
const unsigned char PY_mb_zuan  []={"��߬������"};
const unsigned char PY_mb_zui   []={"��������ީ��"};
const unsigned char PY_mb_zun   []={"��������ߤ"};
const unsigned char PY_mb_zuo   []={"�����������������������������������"};



//ƴ�������Ľṹ������
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
//ƴ�������Ľṹ�������ָ��
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
