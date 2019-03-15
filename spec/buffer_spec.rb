# frozen_string_literal: true

RSpec.describe Buffer do
  it 'has a version number' do
    expect(Buffer::VERSION).not_to be nil
  end

  let(:back) do
    Enumerator.new do |yielder|
      yielder << 1
      yielder << 2
      yielder << 3
    end
  end

  subject(:buffer) { Buffer.create back }

  it 'can be constructed with an enumerable' do
    expect { subject }.not_to raise_error
  end

  it 'has initial capacity == back.count' do
    expect(subject.capacity).to eq back.count
  end

  it 'has initially remaining == capacity' do
    expect(subject.remaining).to eq subject.capacity
  end

  it 'cannot be copied with start > pos' do
    expect { subject.copy(start: 1, pos: 0) }.to raise_error RuntimeError
  end

  it 'cannot be copied with pos > lim' do
    expect { subject.copy(pos: 1, lim: 0) }.to raise_error RuntimeError
  end

  it 'cannot be copied with lim > end' do
    expect { subject.copy(lim: 1, end: 0) }.to raise_error RuntimeError
  end

  it 'cannot be copied with end > count' do
    expect { subject.copy(end: back.count + 1) }.to raise_error RuntimeError
  end
end
