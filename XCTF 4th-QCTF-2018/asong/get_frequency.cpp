#include<iostream>
#include<cstring>
using namespace std;
int get_character_new_index(char a1)
{
  int result; // rax

  result = (a1 - '\n');
  switch ( a1 )
  {
    case '\n':
      result = (a1 + 35);
      break;
    case ' ':
    case '!':
    case '"':
      result = (a1 + 10);
      break;
    case '\'':
      result = (a1 + 2);
      break;
    case ',':
      result = (a1 - 4);
      break;
    case '.':
      result = (a1 - 7);
      break;
    case ':':
    case ';':
      result = (a1 - 21);
      break;
    case '?':
      result = (a1 - 27);
      break;
    case '_':
      result = (a1 - 49);
      break;
    default:
      if ( a1 <= '/' || a1 > '0' )
      {
        if ( a1 <= '@' || a1 > 'Z' )
        {
          if ( a1 > '`' && a1 <= 'z' )
            result = (a1 - 87);
        }
        else
        {
          result = (a1 - 55);
        }
      }
      else
      {
        result = (a1 - 48);
      }
      break;
  }
  return result;
}
int main(){
    int get_ch[80]={0};
    const char * text="There's_a_girl_but_I_let_her_get_away\nIt's_all_my_fault_cause_pride_got_in_the_way\nAnd_I'd_be_lying_if_I_said_I_was_OK\nAbout_that_girl_the_one_I_let_get_away\nI_keep_saying_no\nThis_can't_be_the_way_we're_supposed_to_be\nI_keep_saying_no\nThere's_gotta_be_a_way_to_get_you_close_to_me\nNow_I_know_you_gotta\nSpeak_up_if_you_want_somebody\nCan't_let_him_get_away_oh_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nNo_no_no_no\nThere's_no_hope_for_the_broken_heart\nNo_no_no_no\nThere's_no_hope_for_the_broken\nThere's_a_girl_but_I_let_her_get_away\nIt's_my_fault_cause_I_said_I_needed_space\nI've_been_torturing_myself_night_and_day\nAbout_that_girl_the_one_I_let_get_away\nI_keep_saying_no\nThis can't be the way we're supposed to be\nI keep saying no\nThere's gotta be a way to get you\nThere's gotta be a way\nTo_get_you_close_to_me\nYou_gotta\nSpeak_up_if_you_want_somebody\nCan't_let_him_get_away_oh_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nNo_no_no_no\nThere's_no_hope_for_the_broken_heart\nNo no no no\nThere's no hope for the broken\nNo home for me\nNo home cause I'm broken\nNo room to breathe\nAnd I got no one to blame\nNo home for me\nNo_home_cause_I'm_broken\nAbout_that_girl\nThe_one_I_let_get_away\nSo_you_better\nSpeak_up_if_you_want_somebody\nYou_can't_let_him_bet_away_no_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nDon't_you_know\nNo_no_no_no\nThere's_no_hope_for_the_broken_hearty\nDon't you know\nNo no no no\nThere's no hope for the broken\nOh\nYou don't wanna lose at love\nIt's only gonna hurt too much\nI'm telling you\nYou_don't_wanna_lose_at_love\nIt's_only_gonna_hurt_too_much\nI'm_telling_you\nYou_don't_wanna_lose_at_love\nCause_there's_no_hope_for_the_broken_heart\nThat_girl\nThe_one_I_let_get_away\n";
    for(int i=0;i<strlen(text);++i){//模拟反汇编代码进行字频读取
        get_ch[get_character_new_index(text[i])]++;
    }
    for(int i=33;i<126;++i){//生成字符与下标的对应关系
        cout<<get_character_new_index(i)<<":"<<"\""<<char(i)<<"\""<<',';
    }
    cout<<endl;
    for(int i=0;i<80;++i){
        cout<<get_ch[i]<<',';
    }
    return 0;
}

/*
43:"!",44:""",25:"#",26:"$",27:"%",28:"&",41:"'",30:"(",31:")",32:"*",33:"+",40:",",35:"-",39:".",37:"/",0:"0",39:"1",40:"2",41:"3",42:"4",43:"5",44:"6",45:"7",46:"8",47:"9",37:":",38:";",50:"<",51:"=",52:">",36:"?",54:"@",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F",16:"G",17:"H",18:"I",19:"J",20:"K",21:"L",22:"M",23:"N",24:"O",25:"P",26:"Q",27:"R",28:"S",29:"T",30:"U",31:"V",32:"W",33:"X",34:"Y",35:"Z",81:"[",82:"\",83:"]",84:"^",46:"_",86:"`",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f",16:"g",17:"h",18:"i",19:"j",20:"k",21:"l",22:"m",23:"n",24:"o",25:"p",26:"q",27:"r",28:"s",29:"t",30:"u",31:"v",32:"w",33:"x",34:"y",35:"z",113:"{",114:"|",115:"}",
0,0,0,0,0,0,0,0,0,0,104,30,15,29,169,19,38,67,60,0,20,39,28,118,165,26,0,61,51,133,45,7,34,0,62,0,0,0,0,0,0,40,71,0,0,66,245,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*/