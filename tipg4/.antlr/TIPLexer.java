// Generated from /Users/joshuatapp/Documents/UVA/CS4620/sipc-tapp/tipg4/TIP.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TIPLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, MUL=12, DIV=13, ADD=14, SUB=15, GT=16, LT=17, GTE=18, 
		LTE=19, EQ=20, NE=21, MOD=22, LNOT=23, LAND=24, LOR=25, DEC=26, INC=27, 
		LEN=28, LSBR=29, RSBR=30, BY=31, OF=32, DDOT=33, NUMBER=34, BOOLEAN=35, 
		KALLOC=36, KINPUT=37, KWHILE=38, KIF=39, KFOR=40, KELSE=41, KVAR=42, KRETURN=43, 
		KNULL=44, KOUTPUT=45, KERROR=46, KTRUE=47, KFALSE=48, KNOT=49, KAND=50, 
		KOR=51, IDENTIFIER=52, WS=53, BLOCKCOMMENT=54, COMMENT=55;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "MUL", "DIV", "ADD", "SUB", "GT", "LT", "GTE", "LTE", 
			"EQ", "NE", "MOD", "LNOT", "LAND", "LOR", "DEC", "INC", "LEN", "LSBR", 
			"RSBR", "BY", "OF", "DDOT", "NUMBER", "BOOLEAN", "KALLOC", "KINPUT", 
			"KWHILE", "KIF", "KFOR", "KELSE", "KVAR", "KRETURN", "KNULL", "KOUTPUT", 
			"KERROR", "KTRUE", "KFALSE", "KNOT", "KAND", "KOR", "IDENTIFIER", "WS", 
			"BLOCKCOMMENT", "COMMENT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "','", "')'", "'{'", "'}'", "';'", "'.'", "'&'", "'?'", 
			"':'", "'='", "'*'", "'/'", "'+'", "'-'", "'>'", "'<'", "'>='", "'<='", 
			"'=='", "'!='", "'%'", null, null, null, "'--'", "'++'", "'#'", "'['", 
			"']'", "'by'", "'of'", "'..'", null, null, "'alloc'", "'input'", "'while'", 
			"'if'", "'for'", "'else'", "'var'", "'return'", "'null'", "'output'", 
			"'error'", "'true'", "'false'", "'not'", "'and'", "'or'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			"MUL", "DIV", "ADD", "SUB", "GT", "LT", "GTE", "LTE", "EQ", "NE", "MOD", 
			"LNOT", "LAND", "LOR", "DEC", "INC", "LEN", "LSBR", "RSBR", "BY", "OF", 
			"DDOT", "NUMBER", "BOOLEAN", "KALLOC", "KINPUT", "KWHILE", "KIF", "KFOR", 
			"KELSE", "KVAR", "KRETURN", "KNULL", "KOUTPUT", "KERROR", "KTRUE", "KFALSE", 
			"KNOT", "KAND", "KOR", "IDENTIFIER", "WS", "BLOCKCOMMENT", "COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public TIPLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "TIP.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\29\u013d\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3"+
		"\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r\3"+
		"\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\23\3\24\3"+
		"\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3"+
		"\32\3\32\3\33\3\33\3\33\3\34\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3"+
		" \3 \3 \3!\3!\3!\3\"\3\"\3\"\3#\6#\u00be\n#\r#\16#\u00bf\3$\3$\5$\u00c4"+
		"\n$\3%\3%\3%\3%\3%\3%\3&\3&\3&\3&\3&\3&\3\'\3\'\3\'\3\'\3\'\3\'\3(\3("+
		"\3(\3)\3)\3)\3)\3*\3*\3*\3*\3*\3+\3+\3+\3+\3,\3,\3,\3,\3,\3,\3,\3-\3-"+
		"\3-\3-\3-\3.\3.\3.\3.\3.\3.\3.\3/\3/\3/\3/\3/\3/\3\60\3\60\3\60\3\60\3"+
		"\60\3\61\3\61\3\61\3\61\3\61\3\61\3\62\3\62\3\62\3\62\3\63\3\63\3\63\3"+
		"\63\3\64\3\64\3\64\3\65\3\65\7\65\u0119\n\65\f\65\16\65\u011c\13\65\3"+
		"\66\6\66\u011f\n\66\r\66\16\66\u0120\3\66\3\66\3\67\3\67\3\67\3\67\7\67"+
		"\u0129\n\67\f\67\16\67\u012c\13\67\3\67\3\67\3\67\3\67\3\67\38\38\38\3"+
		"8\78\u0137\n8\f8\168\u013a\138\38\38\3\u012a\29\3\3\5\4\7\5\t\6\13\7\r"+
		"\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25"+
		")\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O"+
		")Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67m8o9\3\2\7\3\2\62;\5\2C\\"+
		"aac|\6\2\62;C\\aac|\5\2\13\f\17\17\"\"\4\2\f\f\17\17\2\u0142\2\3\3\2\2"+
		"\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3"+
		"\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2"+
		"\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2"+
		"\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2"+
		"\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3"+
		"\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2"+
		"\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2"+
		"W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3"+
		"\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\2o\3\2\2"+
		"\2\3q\3\2\2\2\5s\3\2\2\2\7u\3\2\2\2\tw\3\2\2\2\13y\3\2\2\2\r{\3\2\2\2"+
		"\17}\3\2\2\2\21\177\3\2\2\2\23\u0081\3\2\2\2\25\u0083\3\2\2\2\27\u0085"+
		"\3\2\2\2\31\u0087\3\2\2\2\33\u0089\3\2\2\2\35\u008b\3\2\2\2\37\u008d\3"+
		"\2\2\2!\u008f\3\2\2\2#\u0091\3\2\2\2%\u0093\3\2\2\2\'\u0096\3\2\2\2)\u0099"+
		"\3\2\2\2+\u009c\3\2\2\2-\u009f\3\2\2\2/\u00a1\3\2\2\2\61\u00a3\3\2\2\2"+
		"\63\u00a5\3\2\2\2\65\u00a7\3\2\2\2\67\u00aa\3\2\2\29\u00ad\3\2\2\2;\u00af"+
		"\3\2\2\2=\u00b1\3\2\2\2?\u00b3\3\2\2\2A\u00b6\3\2\2\2C\u00b9\3\2\2\2E"+
		"\u00bd\3\2\2\2G\u00c3\3\2\2\2I\u00c5\3\2\2\2K\u00cb\3\2\2\2M\u00d1\3\2"+
		"\2\2O\u00d7\3\2\2\2Q\u00da\3\2\2\2S\u00de\3\2\2\2U\u00e3\3\2\2\2W\u00e7"+
		"\3\2\2\2Y\u00ee\3\2\2\2[\u00f3\3\2\2\2]\u00fa\3\2\2\2_\u0100\3\2\2\2a"+
		"\u0105\3\2\2\2c\u010b\3\2\2\2e\u010f\3\2\2\2g\u0113\3\2\2\2i\u0116\3\2"+
		"\2\2k\u011e\3\2\2\2m\u0124\3\2\2\2o\u0132\3\2\2\2qr\7*\2\2r\4\3\2\2\2"+
		"st\7.\2\2t\6\3\2\2\2uv\7+\2\2v\b\3\2\2\2wx\7}\2\2x\n\3\2\2\2yz\7\177\2"+
		"\2z\f\3\2\2\2{|\7=\2\2|\16\3\2\2\2}~\7\60\2\2~\20\3\2\2\2\177\u0080\7"+
		"(\2\2\u0080\22\3\2\2\2\u0081\u0082\7A\2\2\u0082\24\3\2\2\2\u0083\u0084"+
		"\7<\2\2\u0084\26\3\2\2\2\u0085\u0086\7?\2\2\u0086\30\3\2\2\2\u0087\u0088"+
		"\7,\2\2\u0088\32\3\2\2\2\u0089\u008a\7\61\2\2\u008a\34\3\2\2\2\u008b\u008c"+
		"\7-\2\2\u008c\36\3\2\2\2\u008d\u008e\7/\2\2\u008e \3\2\2\2\u008f\u0090"+
		"\7@\2\2\u0090\"\3\2\2\2\u0091\u0092\7>\2\2\u0092$\3\2\2\2\u0093\u0094"+
		"\7@\2\2\u0094\u0095\7?\2\2\u0095&\3\2\2\2\u0096\u0097\7>\2\2\u0097\u0098"+
		"\7?\2\2\u0098(\3\2\2\2\u0099\u009a\7?\2\2\u009a\u009b\7?\2\2\u009b*\3"+
		"\2\2\2\u009c\u009d\7#\2\2\u009d\u009e\7?\2\2\u009e,\3\2\2\2\u009f\u00a0"+
		"\7\'\2\2\u00a0.\3\2\2\2\u00a1\u00a2\5c\62\2\u00a2\60\3\2\2\2\u00a3\u00a4"+
		"\5e\63\2\u00a4\62\3\2\2\2\u00a5\u00a6\5g\64\2\u00a6\64\3\2\2\2\u00a7\u00a8"+
		"\7/\2\2\u00a8\u00a9\7/\2\2\u00a9\66\3\2\2\2\u00aa\u00ab\7-\2\2\u00ab\u00ac"+
		"\7-\2\2\u00ac8\3\2\2\2\u00ad\u00ae\7%\2\2\u00ae:\3\2\2\2\u00af\u00b0\7"+
		"]\2\2\u00b0<\3\2\2\2\u00b1\u00b2\7_\2\2\u00b2>\3\2\2\2\u00b3\u00b4\7d"+
		"\2\2\u00b4\u00b5\7{\2\2\u00b5@\3\2\2\2\u00b6\u00b7\7q\2\2\u00b7\u00b8"+
		"\7h\2\2\u00b8B\3\2\2\2\u00b9\u00ba\7\60\2\2\u00ba\u00bb\7\60\2\2\u00bb"+
		"D\3\2\2\2\u00bc\u00be\t\2\2\2\u00bd\u00bc\3\2\2\2\u00be\u00bf\3\2\2\2"+
		"\u00bf\u00bd\3\2\2\2\u00bf\u00c0\3\2\2\2\u00c0F\3\2\2\2\u00c1\u00c4\5"+
		"_\60\2\u00c2\u00c4\5a\61\2\u00c3\u00c1\3\2\2\2\u00c3\u00c2\3\2\2\2\u00c4"+
		"H\3\2\2\2\u00c5\u00c6\7c\2\2\u00c6\u00c7\7n\2\2\u00c7\u00c8\7n\2\2\u00c8"+
		"\u00c9\7q\2\2\u00c9\u00ca\7e\2\2\u00caJ\3\2\2\2\u00cb\u00cc\7k\2\2\u00cc"+
		"\u00cd\7p\2\2\u00cd\u00ce\7r\2\2\u00ce\u00cf\7w\2\2\u00cf\u00d0\7v\2\2"+
		"\u00d0L\3\2\2\2\u00d1\u00d2\7y\2\2\u00d2\u00d3\7j\2\2\u00d3\u00d4\7k\2"+
		"\2\u00d4\u00d5\7n\2\2\u00d5\u00d6\7g\2\2\u00d6N\3\2\2\2\u00d7\u00d8\7"+
		"k\2\2\u00d8\u00d9\7h\2\2\u00d9P\3\2\2\2\u00da\u00db\7h\2\2\u00db\u00dc"+
		"\7q\2\2\u00dc\u00dd\7t\2\2\u00ddR\3\2\2\2\u00de\u00df\7g\2\2\u00df\u00e0"+
		"\7n\2\2\u00e0\u00e1\7u\2\2\u00e1\u00e2\7g\2\2\u00e2T\3\2\2\2\u00e3\u00e4"+
		"\7x\2\2\u00e4\u00e5\7c\2\2\u00e5\u00e6\7t\2\2\u00e6V\3\2\2\2\u00e7\u00e8"+
		"\7t\2\2\u00e8\u00e9\7g\2\2\u00e9\u00ea\7v\2\2\u00ea\u00eb\7w\2\2\u00eb"+
		"\u00ec\7t\2\2\u00ec\u00ed\7p\2\2\u00edX\3\2\2\2\u00ee\u00ef\7p\2\2\u00ef"+
		"\u00f0\7w\2\2\u00f0\u00f1\7n\2\2\u00f1\u00f2\7n\2\2\u00f2Z\3\2\2\2\u00f3"+
		"\u00f4\7q\2\2\u00f4\u00f5\7w\2\2\u00f5\u00f6\7v\2\2\u00f6\u00f7\7r\2\2"+
		"\u00f7\u00f8\7w\2\2\u00f8\u00f9\7v\2\2\u00f9\\\3\2\2\2\u00fa\u00fb\7g"+
		"\2\2\u00fb\u00fc\7t\2\2\u00fc\u00fd\7t\2\2\u00fd\u00fe\7q\2\2\u00fe\u00ff"+
		"\7t\2\2\u00ff^\3\2\2\2\u0100\u0101\7v\2\2\u0101\u0102\7t\2\2\u0102\u0103"+
		"\7w\2\2\u0103\u0104\7g\2\2\u0104`\3\2\2\2\u0105\u0106\7h\2\2\u0106\u0107"+
		"\7c\2\2\u0107\u0108\7n\2\2\u0108\u0109\7u\2\2\u0109\u010a\7g\2\2\u010a"+
		"b\3\2\2\2\u010b\u010c\7p\2\2\u010c\u010d\7q\2\2\u010d\u010e\7v\2\2\u010e"+
		"d\3\2\2\2\u010f\u0110\7c\2\2\u0110\u0111\7p\2\2\u0111\u0112\7f\2\2\u0112"+
		"f\3\2\2\2\u0113\u0114\7q\2\2\u0114\u0115\7t\2\2\u0115h\3\2\2\2\u0116\u011a"+
		"\t\3\2\2\u0117\u0119\t\4\2\2\u0118\u0117\3\2\2\2\u0119\u011c\3\2\2\2\u011a"+
		"\u0118\3\2\2\2\u011a\u011b\3\2\2\2\u011bj\3\2\2\2\u011c\u011a\3\2\2\2"+
		"\u011d\u011f\t\5\2\2\u011e\u011d\3\2\2\2\u011f\u0120\3\2\2\2\u0120\u011e"+
		"\3\2\2\2\u0120\u0121\3\2\2\2\u0121\u0122\3\2\2\2\u0122\u0123\b\66\2\2"+
		"\u0123l\3\2\2\2\u0124\u0125\7\61\2\2\u0125\u0126\7,\2\2\u0126\u012a\3"+
		"\2\2\2\u0127\u0129\13\2\2\2\u0128\u0127\3\2\2\2\u0129\u012c\3\2\2\2\u012a"+
		"\u012b\3\2\2\2\u012a\u0128\3\2\2\2\u012b\u012d\3\2\2\2\u012c\u012a\3\2"+
		"\2\2\u012d\u012e\7,\2\2\u012e\u012f\7\61\2\2\u012f\u0130\3\2\2\2\u0130"+
		"\u0131\b\67\2\2\u0131n\3\2\2\2\u0132\u0133\7\61\2\2\u0133\u0134\7\61\2"+
		"\2\u0134\u0138\3\2\2\2\u0135\u0137\n\6\2\2\u0136\u0135\3\2\2\2\u0137\u013a"+
		"\3\2\2\2\u0138\u0136\3\2\2\2\u0138\u0139\3\2\2\2\u0139\u013b\3\2\2\2\u013a"+
		"\u0138\3\2\2\2\u013b\u013c\b8\2\2\u013cp\3\2\2\2\t\2\u00bf\u00c3\u011a"+
		"\u0120\u012a\u0138\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}