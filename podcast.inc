<?php
/*
define("RSS_TITLE","MUSIC PLAYER");
define("FILE_FOLDER","/mnt/share_web/Music/Game Music/");
define("FILE_WEB","http://192.168.1.251/luv/Music/Game Music/")
define("FILE_MAX","200");
*/

//システムで使う定数
define("FILE_WEB_ENCODED",encodeaddr(FILE_WEB));
define("FILE_EXT",".mp3");
define("NOW_DATE",date('r', time()));//dateは固定で。常に更新されるために
/*
 * 本体の処理開始
 */

	//ファイル取得
	function outPodcast(){
		$list = getFileLists();
		$listsize = count($list);
		outHeader($listsize);
		$itemmax = min($listsize,FILE_MAX);
		$randidx = array_rand($list,$itemmax);
		foreach($randidx as $cnt){
			outItem($list[$cnt]);
		}
		outFooter();
	}

	//ヘッダ出力
	function outHeader($listsize){
		header('Content-Type: text/xml; charset=utf-8');
		echo '<?xml version="1.0" encoding="UTF-8"?>';
		echo '<rss version="2.0" xmlns:media="http://search.yahoo.com/mrss/">';
		echo '<channel>';
        echo '<title>'.RSS_TITLE.'</title>';
?>
<link></link>
<description><?php echo FILE_MAX; ?> items from total <?php echo $listsize ?> items.</description>
<language>ja</language>
<copyright>deleloped by PSI 2008</copyright>
<?php
	}
	function outFooter(){
?>
</channel>
</rss>
<?php
	}

	function outItem($path){
?>
<item>
<title><?php
		echo htmlspecialchars(mb_convert_encoding(my_basename($path),"UTF-8","sjis-win,Shift_JIS,ASCII,SJIS,JIS,EUC-JP"),ENT_COMPAT,'UTF-8');
?></title>
<link></link> 
<description></description>
<author></author>
<pubDate><?php echo NOW_DATE; ?></pubDate>
<enclosure url="<?php echo FILE_WEB_ENCODED;echo encodeurl($path);?>" type="audio/mp3" /> 
</item>
<?php
	}

//絶対パス、相対パス
function getFileLists(&$list = array(),$abpath = FILE_FOLDER,$rlpath = ''){
	if(is_dir($abpath) && ($dir = opendir($abpath))){
		while(($file = readdir($dir)) !== false){
			if(is_dir($abpath.$file)){
				if($file == '.' || $file == '..'){
				}else{
					getFileLists($list,$abpath.$file.'/',$rlpath.$file.'/');
				}
			}else{
				//特定の拡張子だけ集める
				if(endsWith($file,FILE_EXT)){
					$list[] = $rlpath.$file;
				}
			}
		}
	}
	return $list;
}
function endsWith( $str, $sub ) {
   return ( substr( $str, strlen( $str ) - strlen( $sub ) ) === $sub );
}

function encodeurl($path){
	$array = explode("/",$path);
	foreach($array as &$item){
		$item = rawurlencode($item);
	}
	return implode("/",$array);
}

function encodeaddr($path){
	$array = explode("/",$path);
	foreach($array as &$item){
		if($item != "http:"){
			$item = rawurlencode($item);
		}
	}
	return implode("/",$array);
}

function my_basename($path){
	return implode(array_diff( explode('/',$path) ,explode('/',dirname($path)))); 
}

?>
