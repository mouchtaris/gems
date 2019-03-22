#:!rake -f Rakefile spec

RSpec.describe Args do
  it "has a version number" do
    expect(Args::VERSION).not_to be nil
  end

  it "does something useful" do
    expect(false).not_to eq(true)
  end

  describe Args::Schematic do
    SCHEMA = Hash[
      a_type: Class.new,
      array_of: Array[Class.new],
      struct_of: Hash[
        x: Integer,
        y: Integer,
      ],
      tuple: Array[String, Integer],
      any_of: Args.or(String, Symbol),
      any_combo_deal: Args.or(
        Array[Hash[x: Integer, y: Integer]],
        Hash[points: Array[Integer]],
      ),
    ]

    let(:passing) do
      Hash[
        a_type: SCHEMA[:a_type].new,
        array_of: Array.new(20) { SCHEMA.dig(:array_of, 0).new },
        struct_of: { x: 12, y: 15 },
        tuple: ['one', 1, 'two', 2],
        any_of: :symbol,
        any_combo_deal: [{x: 12, y: 13}, {x: 22, y: 33}],
      ]
    end

    let(:schematic) {
      Class.new(Args::Schematic) do
        const_set :SCHEMA, SCHEMA
      end
    }

    describe 'initializing with passing args' do
      subject { schematic.new(passing) }
      it { expect { subject }.not_to raise_error }
      SCHEMA.each do |name, _|
        it "#{name} is initialized" do
          expect(subject.instance_variable_get :"@#{name}").not_to be nil
        end

        it "exposes #{name} through a reader" do
          expect(subject.send name).to be subject.instance_variable_get(:"@#{name}")
        end
      end
    end

    shared_examples :a_failing_argument_check do |name|
      subject { schematic.new(passing.tap { |p| p[name] = nil }) }

      it 'raises an error' do
        expect { subject }.to raise_error ArgumentError
      end

      it 'mentions the failing variable name' do
        expect { subject }.to raise_error(/#{name}/)
      end
    end
    SCHEMA.each do |name, _|
      describe "with a missing #{name}" do
        it_behaves_like :a_failing_argument_check, name
      end
    end
  end


end
